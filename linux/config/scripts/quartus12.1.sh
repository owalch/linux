#
# Licence file
#
LM_LICENSE_FILE="26010@aberdeen.ch"
LM_LICENSE_FILE=$LM_LICENSE_FILE:26150@aberdeen.ch


#
# Altera Quartus
#
QUARTUS_ROOTDIR=/opt/altera/12.1sp1/quartus
QUARTUS_64BIT=0
ALTERADIR=/opt/altera/12.1sp1/
SOPC_KIT_NIOS2=$ALTERADIR/nios2eds
PATH=$ALTERADIR/quartus/bin:$ALTERADIR/nios2eds/bin:$PATH


#
# Exports
#
export PATH
export ALTERADIR
export SOPC_KIT_NIOS2
export QUARTUS_ROOTDIR 
export LM_LICENSE_FILE
export QUARTUS_64BIT

