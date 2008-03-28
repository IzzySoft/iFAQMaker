<?php
 #############################################################################
 # iFAQMaker                                (c) 2004-2008 by Itzchak Rehberg #
 # written by Itzchak Rehberg <izzysoft AT qumran DOT org>                   #
 # http://www.izzysoft.de/                                                   #
 # ------------------------------------------------------------------------- #
 # This program is free software; you can redistribute and/or modify it      #
 # under the terms of the GNU General Public License (see doc/LICENSE)       #
 # ------------------------------------------------------------------------- #
 # Basic protection against hacking attempts                                 #
 #############################################################################

 /* $Id$ */

#============================================================[ Protection ]===
#----------------------------------------------------[ Request parameters ]---
$id    = $_REQUEST["id"];
$toc   = $_REQUEST["toc"];
$coll  = $_REQUEST["coll"];
$topic = $_REQUEST["topic"];
#-------------------------------------------------------[ Security Checks ]---
if ( (empty($id) && $id!="0") || preg_match("/[^\d]/",$id) ) unset($id);
if ( empty($toc) ) $toc = 0;
elseif ( preg_match("/[^\d]/",$toc) ) $toc = 1;
if ( preg_match("/[^\w]/",$coll) ) unset ($coll);
if ( preg_match("/[^\w]/",$topic) ) unset ($topic);
# Just in case register_globals is turned on:
if (isset($fsFDir))    unset($fsFDir);
if (isset($fsTplDir))  unset($fsTplDir);
if (isset($fsPlugDir)) unset($fsPlugDir);
?>