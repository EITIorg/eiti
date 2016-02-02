#!/usr/bin/env bash
# Helper script that merges simple and small SVG files into big sprites.

function update_sprite() {
  SPRITE="${1}.svg"
  echo "Updating sprite: $SPRITE"
  rm -f ${SPRITE}
  echo '<svg xmlns:svg="http://www.w3.org/2000/svg" xmlns="http://www.w3.org/2000/svg">' >> $SPRITE
  # TODO: Properly extract the svg[id], svg[viewBox] and other required tags.
  #       For now all the attributes that come after the "id" are kept.
  ls -1 ${1}/*.svg | xargs -i{} cat {} | sed -e 's/<svg.*id=/<symbol id=/' -e 's/\/svg>/\/symbol>\n/' | tr -d '[\n\r\t]' >> $SPRITE

  echo '</svg>' >> $SPRITE
  echo "Finished updating sprite: $SPRITE"
}

# Update the sprites.
update_sprite icons
