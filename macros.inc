<?php
 #############################################################################
 # iFAQMaker                                (c) 2004-2006 by Itzchak Rehberg #
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

#======================================================[ Formatting makros ]===
#----------[ Source code: display in a centered box, do NOT use 100% width ]---
$fmCodeOpen  = '<table border="0" align="center"><tr><td><div class="code">';
$fmCodeClose = '</div></td></tr></table>';
#-------------------[ Names e.g. of applications/companies/trademarks/... ]---
$fmNameOpen  = '<b><i>';
$fmNameClose = '</i></b>';
#-------------------------[ Table to describe e.g. commandline parameters ]---
$fmParamTabOpen  = '<table align="center" border="0" cellspacing="0" cellpadding="0" width="90%" style="margin-top:7px;"><tr><td>'
                 . '  <table align="center" border="1px" cellspacing="0" cellpadding="0">';
$fmParamTabClose = "  </table>\n</td></tr></table>";
#------------------------------------------------------[ Make a "DOS-Box" ]---
$fmDosBoxOpen = '<table width="300" align="center" STYLE="background-color:#f0f0f0; border:2px ridge;">'
              . ' <tr><td style="font-size:-1"><pre>';
$fmDosBoxClose = '</pre></td></tr></table>';

?>