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
if ( isset($_REQUEST["id"]) )    $id    = $_REQUEST["id"];
if ( isset($_REQUEST["toc"]) )   $toc   = $_REQUEST["toc"];
if ( isset($_REQUEST["coll"]) )  $coll  = $_REQUEST["coll"];
if ( isset($_REQUEST["topic"]) ) $topic = $_REQUEST["topic"];
#-------------------------------------------------------[ Security Checks ]---
if ( !isset($id) || ((empty($id) && $id!="0")) || preg_match("/[^\d]/",$id) ) unset($id);
if ( empty($toc) ) $toc = 0;
elseif ( preg_match("/[^\d]/",$toc) ) $toc = 1;
if ( !empty($coll) && preg_match("/[^\w]/",$coll) ) unset ($coll);
if ( !empty($topic) && preg_match("/[^\w]/",$topic) ) unset ($topic);
# Just in case register_globals is turned on:
if (isset($fsFdir))    unset($fsFdir);
if (isset($fsTplDir))  unset($fsTplDir);
if (isset($fsPlugDir)) unset($fsPlugDir);
?>