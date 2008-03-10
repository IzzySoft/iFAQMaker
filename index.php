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
#----------------------------------------------------[ Request parameters ]---
$id    = $_REQUEST["id"];
$toc   = $_REQUEST["toc"];
$coll  = $_REQUEST["coll"];
$topic = $_REQUEST["topic"];
#-------------------------------------------------------[ Security Checks ]---
if ( (empty($id) && $id!="0") || preg_match("/[^\d]/",$id) ) unset($id);
if ( empty($toc) ) $toc = 0;
elseif ( preg_match("/[^\d]/",$toc) ) $toc = 1;
if ( preg_match("/[^\w]/",$coll) ) unset ($coll);
if ( preg_match("/[^\w]/",$topic) ) unset ($topic);

#----------------------------------------------------------[ Translations ]---
function lang($str) { // interprete "TransTable"
  GLOBAL $fsLang;
  if (isset($fsLang[$str])) return $fsLang[$str];
  return ucwords(str_replace("_"," ",$str));
}

#--------------------------------------------------------------[ Includes ]---
include("config.inc");
include($fsMacros);
if (file_exists($fsFdir.$fsTrans)) include($fsFdir.$fsTrans);
tplInit();

#=========================================================[ TOC or Topic? ]===
if (!file_exists($fsFdir."$topic.$fsFext")) unset($topic);
if (!isset($topic)) {
  $topic = "index";
  $fsTocStyle = $fsITocStyle;
}
$infile = $fsFdir."$topic.$fsFext";

#=======================================================[ Load the engine ]===
require_once ($fsIncDir."class.htmlfaq.inc");
$faq = new htmlfaq($fsTplDir,$fsTplFile,$fsTocStyle);
$faq->acronyms("defs/acronyms.txt");
$faq->wikidef("defs/wiki.html.txt");
$faq->wiki(1);

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
$faq->parseInput($infile,lang($topic));
$faq->header($fsTitle,$fsCssFile,$fsCharSet);
$faq->parseOutput();
$faq->footer();
?>