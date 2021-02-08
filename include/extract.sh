if [ $1="extract_zip" ] 
then
	SPATH=$2
	DPATH=$3
	FILE=$4
	unzip ${SPATH}/${FILE} -d ${DPATH}
fi

#if [ $1="extract_file_names_zip" ] 
#then
#	SPATH=$2
#	FILE=$3
#	DFILE=$4
#	#unzip -Z -1 ${SPATH}/${FILE}>${DFILE}
#	unzip -Z -1 ../res/test_doc.cbz>FileNames.txt
#fi

