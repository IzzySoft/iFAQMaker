<?php
 #############################################################################
 # iFAQMaker                                (c) 2004-2006 by Itzchak Rehberg #
 # written by Itzchak Rehberg <izzysoft@qumran.org>                          #
 # http://www.qumran.org/homes/izzy/                                         #
 # ------------------------------------------------------------------------- #
 # This program is free software; you can redistribute and/or modify it      #
 # under the terms of the GNU General Public License (see doc/LICENSE)       #
 # ------------------------------------------------------------------------- #
 # Central Unit: Display index or topic (depending on parameters)            #
 #############################################################################

 /* $Id$ */

#=========================================================[ Configuration ]===
function lang($str) { // interprete "TransTable"
  GLOBAL $fsLang;
  if (isset($fsLang[$str])) return $fsLang[$str];
  return ucfirst($str);
}
include("config.inc");
include($fsMacros);
include($fsFdir.$fsTrans);
tplInit();
require_once ($fsIncDir."class.htmlfaq.inc");
$faq = new htmlfaq($fsTplDir,$fsTplFile,$fsTocStyle);

#==================================================[ Activate the PlugIns ]===
for ($fmpc=0;$fmpc<count($fsPlugIn);++$fmpc) {
  include($fsPlugDir.$fsPlugIn[$fmpc].".inc");
}

#=========================================================[ TOC or Topic? ]===
if (isset($_REQUEST["topic"])) {
  $topic = $_REQUEST["topic"];
} else {
  $topic = "index";
  $fsTocStyle = $fsITocStyle;
}

#==========================================================[ Do the Topic ]===
$infile = $fsFdir."$topic.$fsFext";
$fsTitle .= ": ";
if ($topic) { $fsTitle .= lang($topic); } else { $fsTitle .= lang("index"); }

if (is_array($fsNav)) {
 foreach($fsNav as $var=>$val) { // setup additional template variables
  $faq->set_nav($var,$val);
 }
}
$faq->parseInput($infile,lang($topic));
$faq->header($fsTitle,$fsCssFile,$fsCharSet);
$faq->parseOutput();
$faq->footer();
?>