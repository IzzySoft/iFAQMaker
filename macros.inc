<?php
 #############################################################################
 # FAQMaker                                      (c) 2004 by Itzchak Rehberg #
 # written by Itzchak Rehberg <izzysoft@qumran.org>                          #
 # http://www.qumran.org/homes/izzy/                                         #
 # ------------------------------------------------------------------------- #
 # This program is free software; you can redistribute and/or modify it      #
 # under the terms of the GNU General Public License (see doc/LICENSE)       #
 # ------------------------------------------------------------------------- #
 # Setup some formating makros                                               #
 # ------------------------------------------------------------------------- #
 # Here we set up some frequenty used makros, e.g. for text formating. These #
 # can then be used like {variables} (in fact: these ARE variables). To      #
 # prevent "confusion" with other global variables (like those from the      #
 # configuration), it is recommended to "prefix" the variable names with "fm"#
 # (like "FaqMakro) as to be seen in the examples. Add/modify these as you   #
 # like!                                                                     #
 #############################################################################

 /* $Id$ */

#==[ Source code formating: display in a centered box, do NOT use 100% width ]=
$fmCodeOpen  = '<table border="0" align="center"><tr><td><div class="code">';
$fmCodeClose = '</div></td></tr></table>';


?>