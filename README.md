**iFAQMaker** is a simple PHP class to ease the management of FAQs. Basically,
it is a rewrite of the code I used in the online help system of *phpVideoPro*
(and, besides, this rewrite partially goes back there to replace the old code)
- and that is where the, on a first glance, strange-looking syntax for the
input files comes from. The main topics iFAQMaker is intended to cover are:

* Inserting/Deleting/Moving? single topics (within the same FAQ file) without the hassle of reorganizing indexes, numberings and links
* Use of templates to display the FAQ corresponding to the web site design
* Use of user-definable macros for frequently used formattings etc.
* including syntax highlighting, which can be easily extended to support more formats (see the `plugins/` sub-directory)

You can find an API reference in the `doc/api/` sub-directory of this project.
The documentation itself is using *iFAQMaker*: so simply place the entire
project inside your web tree, and invoke the `index.php` with your web browser.

**Note:** Except for adding this README, *iFAQMaker* hasn't been updated since
2008, and probably will not be updated anymore. I've just decided to leave it
„for reference“ as an „archived repo“ at Github before removing it from my
server.