<?php
 #############################################################################
 # iFAQMaker                                     (c) 2004 by Itzchak Rehberg #
 # written by Itzchak Rehberg <izzysoft@qumran.org>                          #
 # http://www.qumran.org/homes/izzy/                                         #
 # ------------------------------------------------------------------------- #
 # This program is free software; you can redistribute and/or modify it      #
 # under the terms of the GNU General Public License (see doc/LICENSE)       #
 # ------------------------------------------------------------------------- #
 # Configuration                                                             #
 #############################################################################

 /* $Id$ */

#=========================================================[ Configuration ]===
#--[ FAQ text files ]--
$fsFdir   = "text/";       // where the faq text files reside
$fsFext   = "txt";         // file extension of the faq text files
$fsTrans  = "trans.inc";   // "TransTable" for file names

#--[ Templates ]--
$fsTplDir = "template/";   // where the template files are located
$fsTplFile= "data.tpl";    // name of the template file to use
$fsIdxTpl = "toc.tpl";     // template file for the index

#--[ Misc ]--
$fsIncDir = "include/";    // where the class files are located. Leave empty
                           // to use the PHP include path - otherwise this
                           // needs the trailing slash
$fsCharSet = "utf-8";      // character set used for the text
#$fsCssFile[]= "main.css"; // which stylesheet to use (URL)
$fsCssFile[]= "default.css"; // you can specify multiple stylesheets
$fsMacros = "macros.inc";  // file holding formating macros
$fsTocStyle = "ul";        // style of the TOC: "ul", "ol" or "" (no toc)
$fsITocStyle = "";         // same for the default index page
$fsTitle = "iFAQMaker";    // basename of the string for the browsers titlebar

#==========================[ Additional placeholders in your template file ]===
function tplInit() { // we call this AFTER reading the "TransTable"
 GLOBAL $fsNav;
 $fsNav["back"]  = "<A HREF='JavaScript:history.back()'>".lang("back")."</A>";
 $fsNav["index"] = "<A HREF='".$_SERVER["PHP_SELF"]."'>".lang("index")."</A>";
 $fsNav["toc_title"] = lang("toc");
}
?>