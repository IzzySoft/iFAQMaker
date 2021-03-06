<?php
 #############################################################################
 # iFAQMaker                                (c) 2004-2007 by Itzchak Rehberg #
 # written by Itzchak Rehberg <izzysoft AT qumran DOT org>                   #
 # http://www.izzysoft.de/                                                   #
 # ------------------------------------------------------------------------- #
 # This program is free software; you can redistribute and/or modify it      #
 # under the terms of the GNU General Public License (see doc/LICENSE)       #
 # ------------------------------------------------------------------------- #
 # FAQ Generator HTML Class File (extends Base FAQ Class)                    #
 # This "extension" adds the HTML header and footer creation                 #
 # ------------------------------------------------------------------------- #
 # Requirements:                                                             #
 #  * class.faq.inc                                                          #
 #############################################################################

 /* $Id$ */

require_once(dirname(__FILE__)."/class.faq.inc");

#====================================================[ Build page content ]===
/** FAQ Generator
 * @package Api
 * @class htmlfaq
 * @extends faq
 * @author Izzy (izzysoft AT qumran DOT org)
 * @copyright (c) 2004-2007 by Itzchak Rehberg and IzzySoft
 */
class htmlfaq extends faq {

 /** Constructor: Setting up the templates
  * @constructor htmlfaq
  * @param string tpl_dir Directory containing the HTML template files
  * @param string tpl_file Filename of the template file to use
  * @param string toc style of the "table of contents" (ul|ol), empty for no toc
  */
 public function __construct($dir,$file,$toc="") {
  parent::__construct($dir,$file,$toc);
 }

 /** Make the HTML header
  * @method public header
  * @param string title Page title for the browsers title bar
  * @param string css_url URL for the charset to include
  * @param optional string charset Charset used (default: utf-8)
  */
 function header($title,$css,$charset="utf-8") {
   header("Content-type: text/html; charset=$charset");
   echo "<!DOCTYPE HTML PUBLIC '-//W3C//DTD HTML 4.01 Transitional//EN'>\n";
   echo "<HTML><HEAD>\n <TITLE>$title</TITLE>\n"
      . " <META HTTP-EQUIV='Content-Type' CONTENT='text/html; charset=$charset'>\n";
   if (is_array($css)) {
     $cc = count ($css);
     for ($i=0;$i<$cc;++$i) {
       echo  " <LINK HREF='$css[$i]' REL='stylesheet' TYPE='text/css'>\n";
     }
   } else {
     echo  " <LINK HREF='$css' REL='stylesheet' TYPE='text/css'>\n";
   }
   echo "</HEAD><BODY>\n";
 }

 function footer() {
   echo '<DIV ALIGN="center" STYLE="margin-top:7px;margin-bottom:7px;">'
      . '<IMG SRC="'.$this->img->w3c.'" ALT="w3c" WIDTH="14" HEIGHT="14" ALIGN="middle" STYLE="margin-right:3px">'
      . '<SPAN CLASS="footer">Created by <A HREF="http://projects.izzysoft.de/?topic=progs;subject=ifaqmaker" '
      . 'TARGET="_blank">iFAQMaker</A> v'.$this->version.' &copy; 2004-2008 by Itzchak Rehberg '
      . '&amp; <A HREF="http://www.izzysoft.de/" TARGET="_blank">IzzySoft</A></SPAN>'
      . '<IMG SRC="'.$this->img->logo.'" ALT="IzzySoft" WIDTH="14" HEIGHT="14" ALIGN="middle" STYLE="margin-left:3px"></DIV>';
 }

} // end class

?>