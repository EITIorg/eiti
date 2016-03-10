#!/usr/bin/env bash
# Helper script that merges simple and small SVG files into big sprites.

DEBUG=false

function append_symbol {
  local sprite_path="${1}"
  local svg_path="${2}"
  local symbol_name=$(basename $svg_path .svg)

  if [[ ! -f "$svg_path" ]]; then
    echo "   file not found:" $svg_path
    return 0
  fi

  # Optimize the SVG files.
  if [[ -e $(command -v svgo) ]]; then
    local original_svg_path=$svg_path
    svg_path=$(dirname $svg_path)/$(basename $svg_path .svg)".min.svg"

    # @see: https://github.com/svg/svgo
    svgo --config=./svgo.config.yml -i $original_svg_path -o $svg_path
  fi


  if [[ $DEBUG && -f "$original_svg_path" ]]; then
    cat $original_svg_path | sed -e 's/<svg /<symbol id="'$symbol_name.orig'" /' -e 's/\/svg>/\/symbol>\n/' | tr -d '[\n\r\t]' >> $sprite_path
    cat $svg_path | sed -e 's/<svg /<symbol id="'$symbol_name'" /' -e 's/\/svg>/\/symbol>\n/' | tr -d '[\n\r\t]' >> $sprite_path
  else
    cat $svg_path | sed -e 's/<svg /<symbol id="'$symbol_name.min'" /' -e 's/\/svg>/\/symbol>\n/' | tr -d '[\n\r\t]' >> $sprite_path
  fi
}


function update_sprite {
  local sprite="${1}.svg"
  echo "Updating sprite: $sprite"

  # Replace existing sprite with a single <svg> opening tag.
  echo '<svg xmlns:svg="http://www.w3.org/2000/svg" xmlns="http://www.w3.org/2000/svg">' > $sprite

  for f in ${1}/*.svg;
  do
    echo " - processing file: $f";
    append_symbol $sprite $f
  done

  echo '</svg>' >> $sprite
  echo "Finished updating sprite: $sprite"
}

# Update the sprites.
update_sprite icons

if [[ -e $(command -v svgo) ]]; then
  echo "DONE!"
else
  echo -e '\E[33m'"[WARNING] The svgo binary is missing, the sprite generated will be invalid if individual icons are not in the proper format!!!"'\033[0m'
fi
