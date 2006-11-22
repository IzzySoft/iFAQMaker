<?php
 #############################################################################
 # iFAQMaker                                (c) 2004-2006 by Itzchak Rehberg #
 # written by Itzchak Rehberg <izzysoft@qumran.org>                          #
 # http://www.qumran.org/homes/izzy/                                         #
 # ------------------------------------------------------------------------- #
 # This program is free software; you can redistribute and/or modify it      #
 # under the terms of the GNU General Public License (see doc/LICENSE)       #
 # ------------------------------------------------------------------------- #
 # PlugIn for ShellHiLite (include Shell scripts)                            #
 # ------------------------------------------------------------------------- #
 # Usage:                                                                    #
 #   To include a Shell script into your page, simply use the token          #
 #   {shfile("file.sh")} in your input text files (of course, you should     #
 #   replace file.sh by the name of the Shell script to include)             #
 #   file.sh is searched from the directory of your calling script           #
 #############################################################################

 # $Id$

 #===============================================[ Define the placeholder ]===
 $shfile = "shfile";

 #================================================[ setup hilite keywords ]===
 $sh->keywords    = $faq->regexp_pattern_word_file(dirname(__FILE__)."/sh.keywords");
 $sh->typewords   = $faq->regexp_pattern_word_file(dirname(__FILE__)."/sh.types");
 $sh->commonwords = $faq->regexp_pattern_file(dirname(__FILE__)."/sh.common");

 #=================================================[ PlugIn functionality ]===
 function shhighlite($string) {
   GLOBAL $sh;
   if (strpos(trim($string),"#")===0) { // comment
     return "<span class='prg_comment'>$string</span>";
   }
   // commonwords need to be replaced first - or they break all HTML formating
   $string   = preg_replace($sh->commonwords,"<span class='prg_common'>\\1</span>",$string);
   $string   = preg_replace($sh->typewords,"<span class='prg_type'>\\1</span>",$string);
   $string   = preg_replace($sh->keywords,"<span class='prg_key'>\\1</span>",$string);
   return $string;
 }
 function shfile($name) {
   $infile = file($name);
   $output = "";
   for ($i=0;$i<count($infile);++$i) {
     $output .= shhighlite($infile[$i]);
   }
   $dlfile = basename($name);
   $dlname = substr($name,strlen($_SERVER["DOCUMENT_ROOT"]));
   $dllink = "<a href='$dlname'>$dlfile</a>";
   return "<table border='0' align='center'><tr><td><div align='right'>$dllink</div><div class='code_markup'>\n<PRE>$output</PRE>\n</div></td></tr></table>";
 }
?>