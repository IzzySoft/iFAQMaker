<?php
 #############################################################################
 # iFAQMaker                                (c) 2004-2008 by Itzchak Rehberg #
 # written by Itzchak Rehberg <izzysoft AT qumran DOT org>                   #
 # http://www.izzysoft.de/                                                   #
 # ------------------------------------------------------------------------- #
 # This program is free software; you can redistribute and/or modify it      #
 # under the terms of the GNU General Public License (see doc/LICENSE)       #
 # ------------------------------------------------------------------------- #
 # Central Unit: Display index or topic (depending on parameters)            #
 #############################################################################

 /* $Id$ */

#=========================================================[ Configuration ]===
#----------------------------------------------------------[ Translations ]---
function lang($str) { // interprete "TransTable"
  GLOBAL $fsLang;
  if (isset($fsLang[$str])) return $fsLang[$str];
  return ucwords(str_replace("_"," ",$str));
}

#--------------------------------------------------------------[ Includes ]---
include("config.inc");
include($fsMacros);
if (file_exists($fsTrans)) include($fsTrans);
tplInit();

#=========================================================[ TOC or Topic? ]===
if (!file_exists($fsFdir."$topic.$fsFext")) unset($topic);
if (!isset($topic)) {
  $topic = $default_topic;
  $fsTocStyle = $fsITocStyle;
}
$infile = $fsFdir."$topic.$fsFext";

#=======================================================[ Load the engine ]===
require_once ($fsIncDir."class.htmlfaq.inc");
$faq = new htmlfaq($fsTplDir,$fsTplFile,$fsTocStyle);
$faq->acronyms($default_acronyms);
$faq->wikidef($default_wikidef);
$faq->wiki($default_wikimode);

#==================================================[ Activate the PlugIns ]===
for ($fmpc=0;$fmpc<count($fsPlugIn);++$fmpc) {
  include($fsPlugDir.$fsPlugIn[$fmpc].".inc");
  if (function_exists($fsPlugIn[$fmpc]."file"))
    $faq->register_filefunc($fsPlugIn[$fmpc]."file");
}

#==========================================================[ Do the Topic ]===
$fsTitle .= ": ";
if ($topic) { $fsTitle .= lang($topic); } else { $fsTitle .= lang("index"); }

if (is_array($fsNav)) {
 foreach($fsNav as $var=>$val) { // setup additional template variables
  $faq->set_nav($var,$val);
 }
}
$faq->setInputType($default_inputtype);
$faq->parseInput($infile,lang($topic));
$faq->header($fsTitle,$fsCssFile,$fsCharSet);
$faq->parseOutput();
$faq->footer();
?>