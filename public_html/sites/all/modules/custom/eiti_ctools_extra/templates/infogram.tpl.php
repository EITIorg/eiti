<?php

/**
 * Infogr.am template (ASYNC) for the embedded widget.
 */

?>

<div class="infogram-embed" data-id="<?php print $info_id; ?>" data-type="<?php print $info_type; ?>" data-title="<?php print $title; ?>"></div>

<script>!function(e,t,s,i){var n="InfogramEmbeds",o=e.getElementsByTagName("script"),d=o[0],r=/^http:/.test(e.location)?"http:":"https:";if(/^\/{2}/.test(i)&&(i=r+i),window[n]&&window[n].initialized)window[n].process&&window[n].process();else if(!e.getElementById(s)){var a=e.createElement("script");a.async=1,a.id=s,a.src=i,d.parentNode.insertBefore(a,d)}}(document,0,"infogram-async","//e.infogr.am/js/dist/embed-loader-min.js");</script>

<div style="padding:8px 0;font-family:Arial!important;font-size:13px!important;line-height:15px!important;text-align:center;border-top:1px solid #dadada;margin:0 30px">
  <a href="https://infogr.am/96a07b74-829b-4bd3-9a2e-54a6da805e8c" style="color:#989898!important;text-decoration:none!important;" target="_blank" rel="nofollow"><?php print $title; ?></a>
  <br>
  <a href="https://infogr.am" style="color:#989898!important;text-decoration:none!important;" target="_blank" rel="nofollow">Create your own infographics</a>
</div>
