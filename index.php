<?php
 #############################################################################
 # FAQMaker                                      (c) 2004 by Itzchak Rehberg #
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

#=========================================================[ TOC or Topic? ]===
if (isset($_REQUEST["topic"])) {
  $topic = $_REQUEST["topic"];
} else {
  $topic = "index";
  $fsTocStyle = $fsITocStyle;
}

#==========================================================[ Do the Topic ]===
$infile = $fsFdir."$topic.$fsFext";
require_once ($fsIncDir."class.faq.inc");
$fsTitle .= ": ";
if ($topic) { $fsTitle .= lang($topic); } else { $fsTitle .= lang("index"); }

$faq = new faq($fsTplDir,$fsTplFile,$fsTocStyle);
if (is_array($fsNav)) {
 foreach($fsNav as $var=>$val) { // setup additional template variables
  $faq->set_nav($var,$val);
 }
}
$faq->parseInput($infile,lang($topic));
$faq->parseOutput($fsTitle,$fsCssFile,$fsCharSet);

?>