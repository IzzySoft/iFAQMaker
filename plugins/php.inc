<?php
 #############################################################################
 # iFAQMaker                                (c) 2004-2006 by Itzchak Rehberg #
 # written by Itzchak Rehberg <izzysoft@qumran.org>                          #
 # http://www.qumran.org/homes/izzy/                                         #
 # ------------------------------------------------------------------------- #
 # This program is free software; you can redistribute and/or modify it      #
 # under the terms of the GNU General Public License (see doc/LICENSE)       #
 # ------------------------------------------------------------------------- #
 # PlugIn for PHPHiLite (include PHP files)                                  #
 # ------------------------------------------------------------------------- #
 # Usage:                                                                    #
 #   To include a PHP file into your page, simply use the token              #
 #   {phpfile("file.php")} in your input text files (of course, you should   #
 #   replace file.php by the name of the PHP file to include)                #
 #   file.php is searched from the directory of your calling script          #
 #   {phpfile2("file.php")} will use an alternative hiliter.                 #
 #############################################################################

 #===============================================[ Define the placeholder ]===
 $phpfile  = "phpfile";
 $phpfile2 = "phpfile2";

 #================================================[ setup hilite keywords ]===
 $php->keywords    = $faq->regexp_pattern_word_file(dirname(__FILE__)."/php.keys1");
 $php->keywords2   = $faq->regexp_pattern_word_file(dirname(__FILE__)."/php.keys2");
 $php->typewords   = $faq->regexp_pattern_word_file(dirname(__FILE__)."/php.ctrl");
 $php->commonwords = $faq->regexp_pattern_file(dirname(__FILE__)."/php.common");
 $php->constants   = $faq->regexp_pattern_word_file(dirname(__FILE__)."/php.const");

 #=================================================[ PlugIn functionality ]===
 function phphighlite($string) {
   GLOBAL $php;
   if (strpos(trim($string),"#")===0||strpos(trim($string),"//")===0) { // comment
     $string = str_replace("{","&#123;",htmlspecialchars($string));
     return "<span class='prg_comment'>$string</span>";
   }
   $string = htmlspecialchars($string,ENT_NOQUOTES);
   // commonwords need to be replaced first - or they break all HTML formating
   $string   = preg_replace($php->commonwords,"<span class='prg_common'>\\1</span>",$string);
   $string   = preg_replace($php->keywords,"<span class='prg_key'>\\1</span>",$string);
   $string   = preg_replace($php->keywords2,"<span class='prg_key'>\\1</span>",$string);
   $string   = preg_replace($php->typewords,"<span class='prg_type'>\\1</span>",$string);
   $string   = preg_replace($php->constants,"<span class='prg_type'>\\1</span>",$string);
   return str_replace("{","&#123;",$string);
 }
 function mkfile($name,$internal=TRUE) {
   if ($internal) {
     $output = str_replace("{","&#123;",highlight_file($name,TRUE));
   } else {
     $infile = file($name);
     $output = "";
     for ($i=0;$i<count($infile);++$i) {
       $output .= phphighlite($infile[$i]);
     }
   }
   $dlfile = basename($name);
   $dlname = substr($name,strlen($_SERVER["DOCUMENT_ROOT"]));
   $dllink = "<a href='$dlname'>$dlfile</a>";
   return "<table border='0' align='center'><tr><td><div align='right'>$dllink</div><div class='code_markup'>\n<PRE>$output</PRE>\n</div></td></tr></table>";
 }
 function phpfile($name) {
   return mkfile($name);
 }
 function phpfile2($name) {
   return mkfile($name,FALSE);
 }
?>