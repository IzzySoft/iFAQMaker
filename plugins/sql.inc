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

 $sqlfile = "sqlfile";

 #================================================[ setup hilite keywords ]===
 $sql->list = file(dirname(__FILE__)."/sql.keywords");
 $sql->keywords = "/\b(";
 $lc = count($sql->list);
 for ($i=0;$i<$lc;++$i) {
   $sql->keywords .= trim($sql->list[$i])."|";
 }
 $sql->keywords = substr($sql->keywords,0,strlen($sql->keywords)-1).")\b/i";
 $sql->list = file(dirname(__FILE__)."/sql.types");
 $sql->typewords = "/\b(";
 $lc = count($sql->list);
 for ($i=0;$i<$lc;++$i) {
   $sql->typewords .= trim($sql->list[$i])."|";
 }
 $sql->typewords = substr($sql->typewords,0,strlen($sql->typewords)-1).")\b/i";
 $sql->list = file(dirname(__FILE__)."/common.token");
 $sql->commonwords = "/(";
 $lc = count($sql->list);
 for ($i=0;$i<$lc;++$i) {
   $sql->commonwords .= trim($sql->list[$i])."|";
 }
 $sql->commonwords = substr($sql->commonwords,0,strlen($sql->commonwords)-1).")/i";

 function sqlhighlite($string) {
   GLOBAL $sql;
   if (strpos(trim($string),"--")===0) { // comment
     return "<span class='prg_comment'>$string</span>";
   }
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