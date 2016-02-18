#!/usr/bin/perl
#
# leo.pl Version 2.09: English<->German Dictionary
#
# Author/Copyright (c) 2012: Christian Birchinger <cbirchinger@netswarm.net>
# All rights reserved.
#
# Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the
# "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge,
# publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so,
# subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
# MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE
# FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
# WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
#

use strict;
use Socket;
use Getopt::Std;

my ($maxwords, $foundhits, $words, $owords, $outputmode, $noheader, $english, $german, $text);

# -p plaintext(no bold) / -i ircstyle bold / -h help / -n no header / -c <maxoutput>
our ($opt_h, $opt_n, $opt_c, $opt_i, $opt_p);
getopts('iphnc:'); 

# display usage if no textstring is defined or -h requested
if ($opt_h || ! $ARGV[0]) {
	(my $basename = $0) =~ s/.*\///;
	print "Usage: $basename \[-pinh\] \[-c \<max. output\>\] \<words\>\n";
	exit
}

if ($opt_n) {$noheader = 1;}

if ( $opt_c =~ /\d+/ ) {$maxwords = $opt_c;}
else {$maxwords = 5;}

if ($opt_i) {$outputmode = 'irc';}
elsif ($opt_p) {$outputmode = 'plain';}
else {$outputmode = 'bold';}

$words = join ' ', @ARGV;
$owords = $words;

$words =~ s/([^[a-zA-Z0..9])/uc(sprintf("%%%02lx", ord $1))/eg;

if (!defined $noheader) {
	if ( $outputmode ne 'irc' ) { $| = 1; };
	print "Searching for \"$owords\", max. output is $maxwords ... ";
}

my $remote = "pda.leo.org" ; my $port = 80;
my $iaddr = inet_aton($remote) || die "no such host: $remote";
my $paddr = sockaddr_in($port, $iaddr);
my $proto = getprotobyname('tcp');
socket(SOCK, PF_INET, SOCK_STREAM, $proto) || die "socket: $!";
connect(SOCK, $paddr) || die "connect: $!";

send SOCK, "GET /?lp=ende&lang=en&searchLoc=0&cmpType=relaxed&relink=off&sectHdr=off&spellToler=std&search=${words}& HTTP/1.0\r\nHost: ${remote}\r\n\r\n",0;
my @htmlresult=<SOCK>;
close(SOCK);

if (grep(/No entry found/, @htmlresult)) {
	print "Search for \"$owords\" produced no results.\n";
	exit
}	

my $html = join('', grep(/ENGLISH.*GERMAN/, @htmlresult));

if (! ${^UTF8LOCALE}) {utf8::decode($html)};

my @output = grep( /getMoreInfo/, split(/\<\/TR\>/i, $html) );
$foundhits = $#output + 1;

if (!defined $noheader) {print "$foundhits matches found.\n"};

if ($foundhits < $maxwords) {$maxwords = $foundhits};

for (my $i=0; $i < $maxwords; $i++){
	$text = $output[$i];
	$text =~ s:&\#\d+;::g;
	$text =~ s:\[[^\[]*\]::g;
	$text =~ s/<(sup)>.*?<\/\1>//g;

	if ($outputmode eq 'plain') {$text =~ s/\<\/*B\>//ig;}
	elsif ($outputmode eq 'irc') {$text =~ s/\<\/*B\>/\002/ig;}
	else {$text =~ s/\<B\>/\033\[1m/ig; $text =~ s/\<\/B\>/\033\[0m/ig;}
	
	($english, $german) = $text =~ /<td onclick="getMoreInfo\(event,'\d+'\);">(.*?)<\/td\>.*<td onclick="getMoreInfo\(event,'\d+'\);">(.*?)<\/td\>/i;
	$english =~ s:<[^>]*>::g; $german =~ s:<[^>]*>::g;

	if ($english =~ /\033\[0m/) {printf "%-36s %s\n", $english,$german; }
	elsif ($english =~ /\002/) {printf "%-30s %s\n", $english,$german; }
	else { printf "%-28s %s\n", $english,$german; }
}
