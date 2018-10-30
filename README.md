# Exchange
Limit order exchange implemented with all standard library. To ensure ordering in the priority_queue timestamping is used. Each order is timestamped at entrance of exchange.

Dependencies:

- Engine doesn't require any dependencies apart from pthread
- Basic test utility is developed using c++ macros.
- Basic logging features are also developed.
- TDD development methodology is used to develop the engine. src/tests folder has all the test cases developed.
- Root folder has test_data with number of test inputs. 
- Currently tested with the Ubuntu 4.13.0-45-generic #50~16.04.1-Ubuntu SMP Wed May 30 11:18:27 UTC 2018 x86_64 x86_64 x86_64 GNU/Linux
- gcc version is ---> gcc (Ubuntu 5.4.0-6ubuntu1~16.04.9) 5.4.0 20160609
- cpp standard 14 is used as development/build/testing.

Installation:

- Installation script is provided at root location of the repository with name install.sh
- Installer creates new directory "build" and run cmake in it to produce build.
- binary and relavant folders are deployed/installed in "deploy" folder in the root.
