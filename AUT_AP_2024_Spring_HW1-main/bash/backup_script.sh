#!/bin/bash
SourcePath=$1
DestPath=$2
CompressionLevel=1
BackupLogPath=$DestPath/backup_log.txt
Directory="${SourcePath##*/}"
BackupFileName="$(date +"%Y-%m-%d")_$Directory.zip"
StartTime=$(date +%s)
echo $BackupFileName
if [[ $# == 2 ]]; then
    echo 2
elif [[ $# == 4 && ($3 == "-c" || $3 == "--compression") ]]; then
    CompressionLevel=$4
    echo 4
else
    echo "Error"
    exit 1
fi
(cd $SourcePath && zip -r -q $BackupFileName . && mv $BackupFileName $DestPath)
date +"%Y-%m-%d" > $BackupLogPath
currentTime=$(date +"%T")
echo "$currentTime UTC" >> $BackupLogPath
uname -a >> $BackupLogPath
echo "Source Path $SourcePath" >> $BackupLogPath
echo "Dest Path $DestPath" >> $BackupLogPath
echo "Compression Level $CompressionLevel" >> $BackupLogPath

# Count the number of files
num_files=$(find $SourcePath -type f | wc -l)
# Count the number of directories (including the top-level directory itself)
num_dirs=$(find $SourcePath -type d | wc -l)
echo "Num File $num_files" >> $BackupLogPath
echo "Num Dir $num_dirs" >> $BackupLogPath
EndTime=$(date +%s)
Duration=$((EndTime - StartTime))
currentTime=$(date +"%T")
echo "$currentTime UTC" >> $BackupLogPath
echo $Duration >> $BackupFileName
#./backup_script.sh /home/lcx/AUP/AUT_AP_2024_Spring_HW1-main/bash/need_backup /home/lcx/AUP/AUT_AP_2024_Spring_HW1-main/bash -c 9