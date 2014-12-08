#!/bin/bash
#

# Color definitions: {{{

# Color Table
# Usage: \E[<fg_col>;<bg_col>mText
#
# Color          Foreground              Background
# -----------------------------------------------------
# black             30                       40
# red               31                       41
# green             32                       42
# yellow            33                       43
# blue              34                       44
# magenta           35                       45
# cyan              36                       46
# white             37                       47
color_red="\E[31m"
color_green="\E[32m"
color_reset="\E[0m"

# $1: color of the message
# $2: message to print in `color`
function print_col {
	printf "$1$2$color_reset\n"
}
#}}}

test_dir="`pwd`/tests"
scanner_cc="Scanner/debug/ScannerTest"
parser_cc="Parser/debug/TestParser"
typer_cc="Parser/debug/TestTyper"
errors=0

# export path to libs
export LD_LIBRARY_PATH=sharedlib:$LD_LIBRARY_PATH

# $1: message to print in red color
function print_err {
  ((errors+=1))
  print_col $color_red "$1"
}

# no parameters expected
function run_test_file {
  # extracts the name of the directory where the test is located
  prefix=`perl -pe 's|(.+?)/.+|\1|' <<< "${test_file#$test_dir/}"`
  case "$prefix" in
    scanner)
      cmd_cc="$scanner_cc"
      ;;
    parser)
      cmd_cc="$parser_cc"
      ;;
    typer)
      cmd_cc="$typer_cc"
      ;;
    *)
      print_err "Error: no test suite found that could handle '$prefix'"
      ;;
  esac

  start=`date +%s%N`
  $cmd_cc $test_file "$cc_flags" > $run_file 2>&1
  end=`date +%s%N`
  duration="$(( (end-start)/1000000 )) ms"

  diff -q $check_file $run_file > /dev/null
  diff_ret=$?

  echo "[run] $test_file"
  if [[ $diff_ret -eq 0 ]]; then
    rm $run_file
    printf "%6s${color_green}Success$color_reset (${duration})\n"
  else
    ((errors+=1))
    printf "%6s${color_red}Failure$color_reset (${duration})\n"
  fi
}

while read -rd "" test_file
do
  check_file="${test_file%.*}.check"
  run_file="${test_file%.*}.run"
  flags_file="${test_file%.*}.flags"

  # if flags file exists read it, otherwise remove flags
  if [ -r $flags_file ]; then
    cc_flags=`cat $flags_file`
  else
    cc_flags=""
  fi

  # check if file exists and is readable, otherwise show error
  if [ ! -r $check_file ]; then
    print_err "Error: check file $check_file does not exist"
  else
    run_test_file
  fi
done < <(find "$test_dir" -name "*.test" -print0)

[ $errors -ne 0 ] && print_col $color_red "\n$errors error(s) occurred"

[ $errors -eq 0 ] && exit 0 || exit 1
