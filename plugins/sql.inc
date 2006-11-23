<?php
 #############################################################################
 # iFAQMaker                                (c) 2004-2006 by Itzchak Rehberg #
 # written by Itzchak Rehberg <izzysoft@qumran.org>                          #
 # http://www.qumran.org/homes/izzy/                                         #
 # ------------------------------------------------------------------------- #
 # This program is free software; you can redistribute and/or modify it      #
 # under the terms of the GNU General Public License (see doc/LICENSE)       #
 # ------------------------------------------------------------------------- #
 # PlugIn for SQLHiLite (include SQL files)                                  #
 # ------------------------------------------------------------------------- #
 # Usage:                                                                    #
 #   To include a SQL file into your page, simply use the token              #
 #   {sqlfile("file.sql")} in your input text files (of course, you should   #
 #   replace file.sql by the name of the SQL file to include)                #
 #   file.sql is searched from the directory of your calling script          #
 #############################################################################

 #===============================================[ Define the placeholder ]===
 $sqlfile = "sqlfile";

 #================================================[ setup hilite keywords ]===
 $sql->keywords    = $faq->regexp_pattern_word_file(dirname(__FILE__)."/sql.keywords");
 $sql->typewords   = $faq->regexp_pattern_word_file(dirname(__FILE__)."/sql.types");
 $sql->commonwords = $faq->regexp_pattern_file(dirname(__FILE__)."/common.token");

 #=================================================[ PlugIn functionality ]===
 function sqlhighlite($string) {
   GLOBAL $sql;
   if (strpos(trim($string),"--")===0) { // comment
     return "<span class='prg_comment'>$string</span>";
     $string = htmlspecialchars($string);
   }
   $string = htmlspecialchars($string,ENT_NOQUOTES);
   // commonwords need to be replaced first - or they break all HTML formating
   $string   = preg_replace($sql->commonwords,"<span class='prg_common'>\\1</span>",$string);
   $string   = preg_replace($sql->keywords,"<span class='prg_key'>\\1</span>",$string);
   $string   = preg_replace($sql->typewords,"<span class='prg_type'>\\1</span>",$string);
   return $string;
 }
 function sqlfile($name) {
   $infile = file($name);
   $output = "";
   for ($i=0;$i<count($infile);++$i) {
     $output .= sqlhighlite($infile[$i]);
   }
   $dlfile = basename($name);
   $dlname = substr($name,strlen($_SERVER["DOCUMENT_ROOT"]));
   $dllink = "<a href='$dlname'>$dlfile</a>";
   return "<table border='0' align='center'><tr><td><div align='right'>$dllink</div><div class='code_markup'>\n<PRE>$output</PRE>\n</div></td></tr></table>";
 }
?>