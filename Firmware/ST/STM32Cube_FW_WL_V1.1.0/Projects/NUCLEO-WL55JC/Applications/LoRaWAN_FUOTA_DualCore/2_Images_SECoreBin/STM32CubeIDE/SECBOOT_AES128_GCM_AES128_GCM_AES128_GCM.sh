#!/bin/bash - 
#Post build for SECBOOT_AES128_GCM_WITH_AES128_GCM
# arg1 is the build directory
# arg2 is the elf file path+name
# arg3 is the bin file path+name
# arg4 is the firmware Id (1/2/3)
# arg5 is the version
# arg6 when present forces "bigelf" generation
projectdir=$1
FileName=${3##*/}
execname=${FileName%.*}
elf=$2
bin=$3
fwid=$4
version=$5

SBSFUBootLoader=$projectdir"/../../.."
userAppBinary=$projectdir"/../../STM32CubeIDE/Binary"

sfu=$userAppBinary"/"$execname".sfu"
sfb=$userAppBinary"/"$execname".sfb"
sign=$userAppBinary"/"$execname".sign"
headerbin=$userAppBinary"/"$execname"sfuh.bin"
bigbinary=$userAppBinary"/SBSFU_"$execname".bin"
elfbackup=$userAppBinary"/SBSFU_"$execname".elf"

nonce=$SBSFUBootLoader"/2_Images_SECoreBin/Binary/nonce.bin"
magic="SFU"$fwid
oemkey=$SBSFUBootLoader"/2_Images_SECoreBin/Binary/OEM_KEY_COMPANY"$fwid"_key_AES_GCM.bin"
partialbin=$userAppBinary"/Partial"$execname".bin"
partialsfb=$userAppBinary"/Partial"$execname".sfb"
partialsfu=$userAppBinary"/Partial"$execname".sfu"
partialsign=$userAppBinary"/Partial"$execname".sign"
partialoffset=$userAppBinary"/Partial"$execname".offset"
ref_userapp=$projectdir"/RefUserApp.bin"
if [ $fwid -eq 2 ]; then
  priorbin=$userAppBinary"/SBSFU_LoRaWAN_End_Node_DualCore_CM0Plus.bin"
  priorbinadd=$userAppBinary"/SBSFU_LoRaWAN_End_Node_DualCore_CM0Plus.bin.baseadd"
  sbsfuelf=$SBSFUBootLoader"/2_Images_SBSFU/STM32CubeIDE/CM4/Debug/SB.elf"
  if [ -e "$priorbinadd" ]; then
    baseadd=`cat $priorbinadd`
    extramergebin=$priorbin"@"$baseadd";"
  fi
else
  sbsfuelf=$SBSFUBootLoader"/2_Images_SBSFU/STM32CubeIDE/CM0PLUS/Debug/SBSFU.elf"
  extramergebin=""
fi
mapping=$SBSFUBootLoader"/Linker_Common/STM32CubeIDE/mapping_fwimg.ld" 
current_directory=`pwd`
cd $1/../../../../../../../Middlewares/ST/STM32_Secure_Engine/Utilities/KeysAndImages
basedir=`pwd`
cd $current_directory
# test if window executable usable
prepareimage=$basedir"/win/prepareimage/prepareimage.exe"
uname | grep -i -e windows -e mingw > /dev/null 2>&1

if [ $? -eq 0 ] && [   -e "$prepareimage" ]; then
  echo "prepareimage with windows executable"
  export PATH=$basedir"\win\prepareimage";$PATH > /dev/null 2>&1
  cmd=""
  prepareimage="prepareimage.exe"
else
  # line for python
  echo "prepareimage with python script"
  prepareimage=$basedir/prepareimage.py
  cmd="python"
fi

echo "$cmd $prepareimage" > $1/output_$fwid.txt
# Make sure we have a Binary sub-folder in UserApp folder
if [ ! -e $userAppBinary ]; then
mkdir $userAppBinary
fi

command=$cmd" "$prepareimage" enc -k "$oemkey" -n "$nonce" "$bin" "$sfu
$command >> $projectdir"/output_"$fwid".txt"
ret=$?
if [ $ret -eq 0 ]; then
  command=$cmd" "$prepareimage" sign -k "$oemkey" -n "$nonce" "$bin" "$sign
  $command >> $projectdir"/output_"$fwid".txt"
  ret=$?
  if [ $ret -eq 0 ]; then 
    command=$cmd" "$prepareimage" pack -m "$magic" -k "$oemkey"  -r 112 -v "$version" -n "$nonce" -f "$sfu" -t "$sign" "$sfb" -o 512"
    $command >> $projectdir"/output_"$fwid".txt"
    ret=$?
    if [ $ret -eq 0 ]; then
      command=$cmd" "$prepareimage" header -m "$magic" -k  "$oemkey" -r 112 -v "$version"  -n "$nonce" -f "$sfu" -t "$sign" -o 512 "$headerbin
      $command >> $projectdir"/output_"$fwid".txt"
      ret=$?
      if [ $ret -eq 0 ]; then
        command=$cmd" "$prepareimage" extract -d SLOT_Active_"$fwid"_header "$mapping
        header=`$command`
        ret=$?
        echo "header $header" >> $projectdir"/output_"$fwid".txt"
        if [ $ret -eq 0 ]; then
          command=$cmd" "$prepareimage" mergev2 -v 0 -e 1 -b "$extramergebin$headerbin"@"$header" -f "$sbsfuelf";"$elf" "$bigbinary
          echo "merge: $command" >> $projectdir"/output_"$fwid".txt"
          $command >> $projectdir"/output_"$fwid".txt"
          ret=$?
          #Partial image generation if reference userapp exists
          if [ $ret -eq 0 ] && [ -e "$ref_userapp" ]; then
            echo "Generating the partial image .sfb"
            echo "Generating the partial image .sfb" >> $projectdir"/output_"$fwid".txt"
            command=$cmd" "$prepareimage" diff -1 "$ref_userapp" -2 "$bin" "$partialbin" -a 16 --poffset "$partialoffset
            $command >> $projectdir"/output_"$fwid".txt"
            ret=$?
            if [ $ret -eq 0 ]; then
              command=$cmd" "$prepareimage" enc -k "$oemkey" -i "$nonce" "$partialbin" "$partialsfu
              $command >> $projectdir"/output_"$fwid".txt"
              ret=$?
              if [ $ret -eq 0 ]; then
                command=$cmd" "$prepareimage" sign -k "$oemkey" -n "$nonce" "$partialbin" "$partialsign
                $command >> $projectdir"/output_"$fwid".txt"
                ret=$?
                if [ $ret -eq 0 ]; then
                  command=$cmd" "$prepareimage" pack -m "$magic" -k "$oemkey" -r 112 -v "$version" -i "$nonce" -f "$sfu" -t "$sign" -o 512 --pfw "$partialsfu" --ptag "$partialsign" --poffset  "$partialoffset" "$partialsfb
                  $command >> $projectdir"/output_"$fwid".txt"
                  ret=$?
                fi
              fi
            fi
          fi
        fi
        if [ $ret -eq 0 ] && [ $# = 6 ]; then
          echo "Generating the global elf file (SBSFU and userApp)"
          echo "Generating the global elf file (SBSFU and userApp)" >> $projectdir"/output_"$fwid".txt"
          uname | grep -i -e windows -e mingw > /dev/null 2>&1
          if [ $? -eq 0 ]; then
            # Set to the default installation path of the Cube Programmer tool
            # If you installed it in another location, please update PATH.
            PATH="C:\\Program Files\\STMicroelectronics\\STM32Cube\\STM32CubeProgrammer\\bin":$PATH > /dev/null 2>&1
            programmertool="STM32_Programmer_CLI.exe"
          else
            which STM32_Programmer_CLI > /dev/null
            if [ $? = 0 ]; then
              programmertool="STM32_Programmer_CLI"
            else
              echo "fix access path to STM32_Programmer_CLI"
            fi
          fi
          command=$programmertool" -ms "$elf" "$headerbin" "$sbsfuelf
          $command >> $projectdir"/output_"$fwid".txt"
          ret=$?
        fi
      fi
    fi
  fi
fi

if [ $ret -eq 0 ]; then
  rm $sign
  rm $sfu
  rm $headerbin
  if [ -e "$ref_userapp" ]; then
    rm $partialbin
    rm $partialsfu
    rm $partialsign
    rm $partialoffset
  fi  
  exit 0
else 
  echo "$command : failed" >> $projectdir"/output_"$fwid".txt"
  if [ -e  "$elf" ]; then
    rm  $elf
  fi
  if [ -e "$elfbackup" ]; then 
    rm  $elfbackup
  fi
  echo $command : failed
  read -n 1 -s
  exit 1
fi
