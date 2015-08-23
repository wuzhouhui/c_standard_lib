                  STANDARD C LIBRARY CODE DISK V. 2.0

This diskette contains all the source code from ``The Standard C Library,''
by P.J. Plauger (Englewood Cliffs, N.J.: Prentice-Hall, 1992). It corrects
a number of errors reported after publication. Hence, the code may differ
from the book in small ways.

Fifteen subdirectories have names that match the standard headers. These
contain all the *.c files presented in the text. (NOTE: Directories limits,
stdarg, and stddef are empty.) The directory _headers contains all the *.h
files presented throughout the text. The directory _test contains all the
t*.c files presented as test programs throughout the text.

The directory _unixvax replicates a number of these files. It also contains
the sample version of raise.c described in the running text for the ULTRIX
(UNIX VAX) operating system. The directory _unix68k contains ``dirty''
versions of these files -- with the conventional UNIX names for system
calls. It also contains the file yvals.h modified for the GCC compiler on
Sun UNIX (680X0) workstations. That version of yvals.h shows how to define
_CPS if you wish to use the UNIX time system call directly. The directory
_tc86 contains the files that must be modified for the Turbo C++ (ANSI C)
compiler. Finaly, the directory _dummy contains simple versions of several
files. Typically, these define functions that can fail all the time. 

Appendix A: Interfaces summarizes what you have to do to make use of this
code. Please note that it is NOT prepackaged ready to go for any given
operating environment.

To license the right to share the source on a network or multiuser system,
to distribute copies of the source code, or to distribute unlinked object
modules, contact:

	Dinkumware, Ltd.
	398 Main Street
	Concord MA  01742
	sales@dinkumware.com
	http://www.dinkumware.com
	+1-508-369-8489
	+1-508-371-9014 FAX

Notwithstanding the legalisms that follow, the author shall gratefully
accept any bug reports, suggested fixes, or suggestions for improvement.
With this code disk, you have already benefited in many ways from such
contributions by others. Please send such information to the above
address, or to:

	P.J. Plauger
	pjp@dinkumware.com


                      RIGHTS AND LIMITATIONS NOTICE

The author (P.J. Plauger) and publisher (Dinkumware, Ltd.) have used their
best efforts in preparing this code. These efforts include the development,
research, and testing of the programs to determine their effectiveness. The
author and publisher shall not be liable in any event for incidental or
consequential damages in connection with, or arising out of, the furnishing,
performance, or use of the software.

If you are an individual person who has purchased a single-user copy of the
machine-readable software (a purchaser), or who has been given access to a
properly licensed copy (a licensee), you are an Authorized User. You, the
Authorized User, must treat your copy of the software ``just like a book,''
except that you may install it on a computer and that you may make a copy of
the software solely for backup or archival purposes. You may not install a
copy of the software for use by any other persons, on either a multi-user
computer, a multi-user network, or a single-user computer. If you as a
purchaser transfer (sell or give) your copy of this software to another
person, you must transfer or destroy any other copies you have made, and
you must transfer a printed copy of this Rights and Limitations Notice. A
licensee may not transfer the software.

An Authorized User may also use and distribute this code only as part of
executable images that cannot be linked to other executable images, and only
provided that the following notice is included prominently in the associated
documentation and as part of the executable image:

Portions of this work are derived from The Standard C Library, copyright (c)
1992 by P.J. Plauger, published by Prentice-Hall, and are used with
permission.

Licenses to install copies of the software on multi-user computers or on
multi-user networks, or to distribute binary object modules, or to
distribute copies of the source files (modified or unmodified) are
available from Dinkumware, Ltd. (phone +1-508-369-8489 or send email to
sales@dinkumware.com).

NEITHER DINKUMWARE, LTD. NOR P.J. PLAUGER MAKE, AND AUTHORIZED USERS HEREBY
EXPRESSSLY WAIVE, ALL WARRANTIES, EXPRESS OR IMPLIED. ALL WARRANTIES OF
MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE OR OF NON INFRINGEMENT
ARE EXPRESSLY EXCLUDED. If Dinkumware, Ltd. is unable to remedy any defect
in The Standard C Library required under the foregoing warranty, the sole
liability of Dinkumware, Ltd. and/or P.J. Plauger's to you shall be limited
to damages actually sustained by you as a result of the unremedied defect
and shall in no event exceed the amount of license fees received hereunder
by Dinkumware, Ltd. as of the date the applicable warranty claim is first
made.

You shall provice no warranties or representations, express or implied, that
give any other user or customer any rights or remedies against Dinkumware,
Ltd. or P.J. Plauger.
