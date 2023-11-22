Obsidian integration/staging tree
================================

http://www.obsidiancoin.org

Copyright (c) 2009-2024 Bitcoin Developers

Copyright (c) 2011-2024 Litecoin Developers

Copyright (c) 2017-2024 Obsidian Developers

What is Obsidian?
----------------

Obsidian is a lite version of litecoin using the same scrypt as a proof-of-work algorithm.
 - 1.5 minute block targets (Litecoin is 2.5 minutes )
 - subsidy halves in 840k blocks (~4 years)
 - ~168 million total coins (Litecoin is 84 million total coins)
 - 21 Block confirmations to spend mined coins (Litecoin is 120 blocks confirmed before you can spend mined coins)

The rest is the same as Bitcoin / litecoin.
 - 100 coins per block
 - 2016 blocks to retarget difficulty

For more information, as well as an immediately useable, binary version of
the Obsidian client sofware, see http://www.obsidiancoin.org.

License
-------

Obsidian is released under the terms of the MIT license. See `COPYING` for more
information or see http://opensource.org/licenses/MIT.

Development process
-------------------

Developers work in their own trees, then submit pull requests when they think
their feature or bug fix is ready.

If it is a simple/trivial/non-controversial change, then one of the Obsidian
development team members simply pulls it.

If it is a *more complicated or potentially controversial* change, then the patch
submitter will be asked to start a discussion with the devs and community.

The patch will be accepted if there is broad consensus that it is a good thing.
Developers should expect to rework and resubmit patches if the code doesn't
match the project's coding conventions (see `doc/coding.txt`) or are
controversial.

The `master` branch is regularly built and tested, but is not guaranteed to be
completely stable. [Tags](https://github.com/obsidian-project/obsidian/tags) are created
regularly to indicate new official, stable release versions of Obsidian.

Testing
-------

Testing and code review is the bottleneck for development; we get more pull
requests than we can review and test. Please be patient and help out, and
remember this is a security-critical project where any mistake might cost people
lots of money.

### Automated Testing

Developers are strongly encouraged to write unit tests for new code, and to
submit new unit tests for old code.

Unit tests for the core code are in `src/test/`. To compile and run them:

    cd src; make -f makefile.unix test

Unit tests for the GUI code are in `src/qt/test/`. To compile and run them:

    qmake BITCOIN_QT_TEST=1 -o Makefile.test bitcoin-qt.pro
    make -f Makefile.test
    ./obsidian-qt_test

