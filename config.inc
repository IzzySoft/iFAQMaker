<?php
 #############################################################################
 # iFAQMaker                                (c) 2004-2008 by Itzchak Rehberg #
 # written by Itzchak Rehberg <izzysoft AT qumran DOT org>                   #
 # http://www.izzysoft.de/                                                   #
 # ------------------------------------------------------------------------- #
 # This program is free software; you can redistribute and/or modify it      #
 # under the terms of the GNU General Public License (see doc/LICENSE)       #
 # ------------------------------------------------------------------------- #
 # Configuration                                                             #
 #############################################################################

 /* $Id$ */

#=========================================================[ Configuration ]===
if (isset($fsIncDir)) unset($fsIncDir); // prevent from overwrite by URL
$fsIncDir = "include/";    // where the class files are located. Leave empty
                           // to use the PHP include path - otherwise this
                           // needs the trailing slash
include($fsIncDir."ifaq_protect.inc");

#--------------------------------------------------------[ FAQ text files ]---
$fsFdir        = "text/";          // where the faq text files reside
$fsFext        = "txt";            // file extension of the faq text files
$fsTrans       = "text/trans.inc"; // "Translation Table"
$default_topic = "index";          // topic to use if none specified in URL

#------------------------------------------------------[ Input definition ]---
$fsMacros          = "macros.inc";        // file holding formating macros
$default_inputtype = "block";             // block or flat mode?
$default_acronyms  = "defs/acronyms.txt"; // Acronym definitions
$default_wikidef   = "defs/wiki.html.txt";// Wiki translations
$default_wikimode  = TRUE;                // enable wiki syntax by default?
$fsCharSet         = "utf-8";             // character set used for the text
#$fsCssFile[]      = "main.css";          // which stylesheet to use (URL)
$fsCssFile[]       = "default.css";       // multiple stylesheets possible
$fsTocStyle        = "ul";                // style of the TOC: "ul", "ol"
                                          // or "" (no toc)
$fsITocStyle       = "";                  // same for the default index page
$fsTitle           = "iFAQMaker";         // basename of the string for the
                                          // browsers titlebar

#-------------------------------------------------------------[ Templates ]---
$fsTplDir  = "template/";   // where the template files are located
$fsTplFile = "data.tpl";    // name of the template file to use
$fsIdxTpl  = "toc.tpl";     // template file for the index

#---------------------------------------------------------------[ PlugIns ]---
$fsPlugDir  = "plugins/";
$fsPlugIn[] = "php";       // PHP Highliter
$fsPlugIn[] = "sql";       // SQL Highliter
$fsPlugIn[] = "sh";        // Shell Highliter

#==========================[ Additional placeholders in your template file ]===
function tplInit() { // we call this AFTER reading the "TransTable"
 GLOBAL $fsNav,$faq;
 $fsNav["back"]  = "<A HREF='JavaScript:history.back()'>".$faq->lang("back")."</A>";
 $fsNav["index"] = "<A HREF='".$_SERVER["PHP_SELF"]."'>".$faq->lang("index")."</A>";
 $fsNav["toc_title"] = $faq->lang("toc");
}
?>