<?php
 #############################################################################
 # iFAQMaker                                (c) 2004-2008 by Itzchak Rehberg #
 # written by Itzchak Rehberg <izzysoft AT qumran DOT org>                   #
 # http://www.izzysoft.de/                                                   #
 # ------------------------------------------------------------------------- #
 # This program is free software; you can redistribute and/or modify it      #
 # under the terms of the GNU General Public License (see doc/LICENSE)       #
 # ------------------------------------------------------------------------- #
 # FAQ Generator Base Class File                                             #
 # ------------------------------------------------------------------------- #
 # Requirements:                                                             #
 #  * class.template.inc                                                     #
 #  * global function: string lang(string) for translations                  #
 #############################################################################

 /* $Id$ */

require_once(dirname(__FILE__)."/class.template.inc");

#====================================================[ Build page content ]===
/** FAQ Generator
 * @package Api
 * @class faq
 * @author Izzy (izzysoft AT qumran DOT org)
 * @copyright (c) 2001-2008 by Itzchak Rehberg and IzzySoft
 */
class faq {

 /** Constructor: Setting up the templates
  * @constructor faq
  * @param string tpl_dir Directory containing the HTML template files
  * @param string tpl_file Filename of the template file to use
  * @param string toc style of the "table of contents" (ul|ol), empty for no toc
  */
 public function __construct($dir,$file,$toc="") {
  $this->version = "0.1.5";
  $this->t = new Template($dir);
  $this->t->set_file(array("main"=>"$file"));
  $this->t->set_block("main","titleblock","titlelist");
  $this->t->set_block("titleblock","textblock","textlist");
  $this->t->set_block("main","tocblock","toclist");
  $this->img = new stdClass();
  $this->img->logo = "islogo.gif";
  $this->img->w3c  = "w3c.jpg";
  $this->toc = $toc;
  $this->toclist = "";
  $this->acronym_def = array();
  $this->acronym_res = array();
  $this->acronym_count = 0;
  $this->wiki_count = 0;
  $this->use_wiki = FALSE;
  // functions whose (only) parameter references a file relative to the script:
  $this->file_funcs = array();
  $this->ffcount = 0;
 }

 /** Set type of input file
  * @method setInputType
  * @param string type Supported types: block (default), flat (implicates wiki
  *        mode to be enabled)
  */
 function setInputType($type) {
   if ($type=="flat") $this->wiki(TRUE);
   $this->inputType = $type;
 }

 /** Register a function whose (only) parameter references a file relative to the script
  *  (mainly used for the HiLite PlugIns)
  * @method register_filefunc
  * @param string function_name name of the function to register
  */
 function register_filefunc($func) {
   $this->file_funcs[] = $func;
   ++$this->ffcount;
 }

 /** Read in acronym definitions
  * @method acronyms
  * @param string filename name of the file to read the acronym definitions from
  */
 function acronyms($file) {
   if (file_exists($file)) {
     $list = file($file);
     @rsort($list);
     $lc = count($list);
     for ($i=0,$k=-1;$i<$lc;++$i) {
       if (trim($list[$i])=="") continue; // skip empty lines
       if (substr(trim($list[$i]),0,1)=="#") continue; // skip comments
       ++$k;
       $pos = strpos($list[$i]," ");
       $nam = substr($list[$i],0,$pos);
       $this->acronym_def[$k] = "/\b$nam(?![^\b]+\<\/acronym)/";
       $this->acronym_res[$k] = '<acronym title="'.str_replace('"',"'",trim(substr($list[$i],$pos +1))).'">'.$nam."</acronym>";
     }
   }
   $this->acronym_count = $k;
 }

 /** Read in Wiki definitions
  * @method wikidef
  * @param string filename name of the file to read the wiki definitions from
  */
 function wikidef($file) {
   if (file_exists($file)) {
     $list = file($file);
     $lc = count($list);
     for ($i=0,$k=-1;$i<$lc;++$i) {
       if (trim($list[$i])=="") continue; // skip empty lines
       if (substr(trim($list[$i]),0,1)=="#") continue; // skip comments
       ++$k;
       $ar = explode(";",$list[$i]);
       $this->wiki_def[$k] = $ar[0];
       $this->wiki_res[$k] = trim($ar[1]);
     }
   }
   $this->wiki_count = $k;
 }

 /** Enable/Disable Wiki replacement
  * @method wiki
  * @param boolean enable
  */
 function wiki($enable) {
   if ($enable && $this->wiki_count > 0) $this->use_wiki = TRUE;
   else $this->use_wiki = FALSE;
 }

 /** Set TOC from WikiSyntax
  * @method setWikiToc
  */
 function setWikiToc() {
   if (empty($this->toc)) return; // no TOC requested
   if (preg_match_all("/^(\={1,6})([^\=]+?)\={1,6}$/ms",$this->wikiText,$matches)) {
     $mc = count($matches[0]); $lastlevel = 0; $list = $this->toc; $this->wikiToc = "";
     for ($i=0;$i<$mc;++$i) {
       $level = strlen($matches[1][$i]);
       if ($level > $lastlevel) {
         $diff = $level - $lastlevel;
         for ($k=0;$k<$diff;++$k) $this->wikiToc .= "<$list>";
       } elseif ($level < $lastlevel) {
         $diff = $lastlevel - $level;
         for ($k=0;$k<$diff;++$k) $this->wikiToc .= "</$list>";
       }
       $href = str_replace(array(" ",'"',"'","{","}","[","]","(",")","^","'","?","!","."),array(""),$matches[2][$i]);
       $this->wikiToc .= "<li><a href='#$href'>".$matches[2][$i]."</li>";
       $this->wikiText = str_replace($matches[0][$i],"<a name='$href'></a>\n".$matches[0][$i],$this->wikiText);
       $lastlevel = $level;
     }
     while ($lastlevel>0) {
       $this->wikiToc .= "</$list>";
       --$lastlevel;
     }
   }
 }

 /** Read the input file
  * @method private fileRead
  * @param string filename name of the file to read
  */
 function fileRead($file) {
  $this->input = file($file);
  if (substr(trim($this->input[0]),0,1)=="!") { // "symbolic link"
    $file = dirname($file) . "/" . trim(substr($this->input[0],1));
    $this->input = file($file);
  }
 }

 /** Parse input text into blocks.
  *  Blocks start with a line containing only the "block header", which
  *  looks like "<pre>[&lt;blockname&gt;|level|hname]</pre>", where:<ul>
  *  <li><i>&lt;blockname&gt;</i> is one of "title", "text" or "eof"</li>
  *  <li><i>level</i> is an integer (or empty) for e.g. &lt;H1&gt;</li>
  *  <li><i>hname</i> is a name (&lt;A NAME="<i>name</i>"&gt;) for references</li></ul>
  *  everything after the <code>&lt;blockname&gt;</code> is optional.
  * @method public parseInput
  * @param string filename input file name
  */
 function parseInput($file,$title="") {
  $this->fileRead($file);
  $lines = count($this->input);
  if ($this->inputType=="flat") {
    $this->wikiText = "";
    for ($i=0;$i<$lines;++$i) {
      $line = $this->input[$i];
      $uline = trim($line);
      if ( substr($uline,0,1) == "#" ) continue; // strip off comments
      $this->wikiText .= $line;
    }
    $this->setWikiToc();
    $this->wikiReplace($this->wikiText);
    $this->textReplace($this->wikiText);
    return;
  }
  $blocknr = -1;
  for ($i=0;$i<$lines;++$i) {
    $line = $this->input[$i];
    $uline = trim($line);
    if ( substr($uline,0,1) == "#" ) continue; // strip off comments
    $mark = preg_match("/^\[(\S+)\]$/",$uline,$hit);
    if ($mark) {
      ++$blocknr;
      $desc = preg_match("/([^\|]+)(\|([^\|]*)(\|(\S*))?)?$/",$hit[1],$set);
      if ( !isset($this->block[$blocknr]) ) $this->block[$blocknr] = new stdClass();
      if ($desc) { // Special settings for this block (usually [title|<level>|<name>])
        $this->block[$blocknr]->type  = $set[1];
        if (!empty($set[2]))
          $this->block[$blocknr]->level = $set[3]; // <h$level>
        else
          $this->block[$blocknr]->level = 1;
        if (!empty($set[4]))
          $this->block[$blocknr]->name  = $set[5]; // <a name=...>
        else
          $this->block[$blocknr]->name  = $blocknr;
      }
      $this->block[$blocknr]->content = "";
      if ($hit[1]=="eof") break;
    } elseif ($blocknr>-1) {
      $this->block[$blocknr]->content .= $line;
    }
  }
  $this->blocks = ++$blocknr;
  for ($k=0;$k<$this->blocks;++$k) {
   $content = $this->block[$k]->content;
   $content = str_replace("\$","&#36;",$content);
   if ($this->block[$k]->type != "title") { // parse wiki style elements
     $this->wikiReplace($content);
   }
   $this->textReplace($content);
   $this->block[$k]->content = $content;
  }

  if (!empty($title)) $this->t->set_var("listtitle",$title);
 } // end parse_input()

 /** Wiki Replacements
  * @method private wikiReplace
  * @param reference string text text to parse (passed by reference)
  */
 function wikiReplace(&$content) {
   if ($this->use_wiki)
     $content = preg_replace($this->wiki_def,$this->wiki_res,$content);
 }

 /** Replace variables and translations
  * @method private textReplace
  * @param reference string text passed by reference
  */
 function textReplace(&$content) {
   if ( preg_match_all("/(?<!\{)\{{1}(?!\{)(.+?)\}{1}(?!\})/",$content,$matches) ) { // replace variables
    for ($i=0;$i<count($matches[0]);$i++) {
      $var = $matches[1][$i];
      $pos = strpos($var,"->");
      if ($pos) { // this is an object {obj->var}
       $obj = substr($var,0,$pos); $prop = substr($var,$pos+2);
       GLOBAL $$obj;
       $rvar = $$obj->$prop;
      } else {
        $tpos = strpos($var,"(");
        if ($tpos) { // this is a function {func()}
          $tdir = $_SERVER["DOCUMENT_ROOT"].dirname($_SERVER["PHP_SELF"])."/";
          $tvar = substr($var,0,$tpos);
          if (in_array($tvar,$this->file_funcs)) // convert relative path to absolute
            $rvar = $tvar($tdir.substr($var,$tpos+2,strpos($var,")")-$tpos-3));
          else
            $rvar = $tvar(substr($var,$tpos+2,strpos($var,")")-$tpos-3));
        } else { // must be a variable ({var} or {var[]}
          if (preg_match_all("/^(.*)\[\"(.*)\"\]\[\"(.*)\"\]$/",$var,$matchme)) { // var["x"]["y"]
            $rvar = $GLOBALS[$matchme[1][0]][$matchme[2][0]][$matchme[3][0]];
          } elseif (preg_match_all("/^(.*)\[\"(.*)\"\]$/",$var,$matchme)) { // var["x"]
            $rvar = $GLOBALS[$matchme[1][0]][$matchme[2][0]];
          } else { // scalar ({var}) is the only thing left
            if ( isset($GLOBALS[$var]) ) $rvar = $GLOBALS[$var];
          }
        }
      }
      $var  = str_replace("/","\/",$var); // need to addslashes for
      $var  = str_replace('"','\"',$var); // preg_replace (the functions
      $var  = str_replace('(','\(',$var); // addslashes and quotemeta do
      $var  = str_replace(')','\)',$var); // not help here
      $var  = str_replace('[','\[',$var);
      $var  = str_replace(']','\]',$var);
      if ( isset($rvar) ) {
        $rvar = str_replace("\$","&#36;",$rvar);
        $content = preg_replace("/\{$var\}/",$rvar,$content);
      }
    }
   }
   if ( preg_match_all("/\*\S+\#/",$content,$matches) ) { // replace translations
    for ($i=0;$i<count($matches[0]);$i++) {
      $var  = substr($matches[0][$i],1,strlen($matches[0][$i])-2);
      $rvar = $this->lang($var);
      $content = preg_replace("/\*$var\#/",$rvar,$content);
    }
   }
   if ($this->acronym_count > 0) { // replace acronyms
     $content = preg_replace($this->acronym_def,$this->acronym_res,$content);
   }
 } // end textReplace

 /** Output the text
  * @method public parseOutput
  */
 function parseOutput() {
  if ($this->inputType=="flat") {
    if (empty($this->toc)) $this->set_nav("toclist","");
    else {
      $this->set_nav("toc",$this->wikiToc);
      $this->t->parse("toclist","tocblock");
    }
    $this->set_nav("titlelist","<tr><td>".$this->wikiText."</td></tr>");
    $this->t->pparse("out","main");
    return;
  }
  $text_open = FALSE; $block_open = 0; $toclevel = 0; $list = $this->toc;
  for ($i=0;$i<$this->blocks;++$i) {
    switch (strtolower($this->block[$i]->type)) {
      case "title" : if (!$text_open && $block_open>0) {
                       $this->set_nav("textlist",""); // init empty textblock
		     }
                     $text_open = FALSE;
                     switch ($block_open) {
                       case 0 : break; // first title just starts here
                       case 1 : $this->t->parse("titlelist","titleblock"); break;
                       default: $this->t->parse("titlelist","titleblock",TRUE);
                     }
                     $this->set_nav("title",trim($this->block[$i]->content));
                     $this->set_nav("t_name",$this->block[$i]->name);
		     $this->set_nav("t_level",$this->block[$i]->level);
                     $this->set_nav("textlist",""); // init empty textblock
		     if (!empty($this->toc)) {
                       $ldiff = $this->block[$i]->level - $toclevel;
                       for ($k=-1;$k>$ldiff;--$k) { // level diff > 1 downstairs
                         $this->toclist .= "</$list>";
                         if ($k==$ldiff+1) $ldiff = -1;
                       }
		       switch ($ldiff) {
		         case -1 : $this->toclist .= "</$list>"; break;
			 case  0 : if ($toclevel>0) $this->toclist .= "</li>"; break;
			 case  1 : $this->toclist .= "<$list>"; break;
			 default : break;
		       }
		       $toclevel = $this->block[$i]->level;
		       $this->toclist .= "<li><a class='toc' href='#".$this->block[$i]->name."'>".trim($this->block[$i]->content)."</a>";
		     }
                     ++$block_open;
                     break;
      case "text"  : $this->set_nav("text",trim($this->block[$i]->content));
                     if ($text_open) {
                       $this->t->parse("textlist","textblock",TRUE);
                     } else {
                       $this->t->parse("textlist","textblock");
                     }
                     $text_open = TRUE;
                     break;
      case "eof"   : break 2;
      default      : break; // echo "<b><i>!!!(".$this->block[$i]->type.")".$this->block[$i]->content."!!!</i></b>\n";
    }
  } // end blocks = end input || eof
  #-- whether to parse the TOC into to the template
  if (empty($this->toc)) {
    $this->set_nav("toclist","");
  } else {
    for ($k=0;$k<$toclevel;++$k) { $this->toclist .= "</li></$list>"; }
       $this->set_nav("toc",$this->toclist);
    $this->t->parse("toclist","tocblock");
  }
  switch ($block_open) { // parse open blocks
    case 0 : break; // nothing to do
    case 1 : $this->t->parse("titlelist","titleblock"); break;
    default: $this->t->parse("titlelist","titleblock",TRUE);
  }
  $this->t->pparse("out","main");
 }

 /** Set template variables. Wrapper around this::t::set_var
  * @method public set_nav
  * @param string name name of template variable
  * @param string content value of template variable
  */
 function set_nav($name,$content) {
   $this->t->set_var($name,$content);
 }

 /** Read list of keywords from a given file and set them up as regexp pattern
  *  All keywords will be matched as "whole words" only (i.e. not as part
  *  of other words)
  *  Used for the hilite plugins
  * @method public regexp_pattern_word_file
  * @param string file name of the file holding the keywords, one by line
  * @return string regexp pattern
  */
 function regexp_pattern_word_file($file) {
   $list = file($file);
   $keywords = "/\b(";
   $lc = count($list);
   for ($i=0;$i<$lc;++$i) {
     $keywords .= trim($list[$i])."|";
   }
   $keywords = substr($keywords,0,strlen($keywords)-1).")\b/i";
   return $keywords;
 }

 /** Read list of keywords from a given file and set them up as regexp pattern
  *  All keywords will be matched as "strings" only (i.e. also as part of
  *  other words)
  *  Used for the hilite plugins
  * @method public regexp_pattern_file
  * @param string file name of the file holding the keywords, one by line
  * @return string regexp pattern
  */
 function regexp_pattern_file($file) {
   $keywords = $this->regexp_pattern_word_file($file);
   return "/".substr($keywords,3,strlen($keywords)-7)."/i";
 }

 /** Translate a string
  *  Returns the replacement as defined by the file read with readTrans(). If no
  *  replacement exists, all underscores are replaced by spaces, and the resulting
  *  words have their first character uppercased.
  * @method lang
  * @param string input
  * @return string translation
  */
 function lang($str) {
   if (isset($this->trans[$str])) return $this->trans[$str];
   return ucwords(str_replace("_"," ",$str));
 }

 /** Read translations from a file
  * @method readTrans
  * @param string filename name of the file to read the translations from
  */
 function readTrans($file) {
   $input = file($file);
   $lines = count($input);
   for ($i=0;$i<$lines;++$i) {
     $line = trim($input[$i]);
     if (empty($line)) continue; // skip empty lines
     if (substr($line,0,1)=="#") continue; // skip comments
     $pos = strpos($input[$i],";");
     $this->trans[substr($input[$i],0,$pos)] = substr($input[$i],$pos+1);
   }
 }

/** Type of the TOC: "ol", "ul" or "" (no TOC)
 * @class faq
 * @attribute private string toc
 */
/** Content of the TOC (to be parsed into {toc})
 * @class faq
 * @attribute private string toclist
 */
/** Content of the parsed input file (one line per cell)
 * @class faq
 * @attribute private array input
 */
/** Content of the parsed input file, splitted into blocks
 * @class faq
 * @attribute private array block
 */
/** Number of blocks created
 * @class faq
 * @attribute private integer blocks
 */

} // end class

?>