# -*- mode: python -*-

from glob import glob
from sys import stdout
from os import path

SharedLibrary('./lib/assignments', glob('./lib/*.c'))
env = Environment(tools = ["default", "doxygen"],
                  CPPPATH = './lib',
                  LIBPATH = './lib')

conf = Configure(env)
if not conf.CheckLibWithHeader('m', 'math.h', 'c'):
    print '''
    Did not find libm.a or m.lib, exiting!
    This library is typically bundled with C runtime.
    If you are seeing this message, you probably need to donwload
    development version of it (i.e. the header files) and put them
    on your include path.

    On RHEL-like system, run:
    $ yum provides '*/math.h'
    to find out what package contains the headers.  Typically, this
    is something like glibc-headers.

    On Debian-like system, run:
    $ apt-cache search math.h
    and then install the missing package.

    On MS Windows, if you have a C compiler, you, most likely,
    already have this library somewhere.  You just didn't configure
    your include path properly.  See this answer for how to locate it:
    <http://stackoverflow.com/a/24186973/5691066>
    '''
    Exit(1)
if conf.CheckLibWithHeader('gc', 'gc.h', 'c'):
    print 'Found garbage collector, compiling with gc enabled.'
    env.Append(CFLAGS = '-DWITH_GC')
else:
    print '''
    Compiling without garbage collector!
    This code may conditionally use Boehm garbage collector.
    It is preferable that you compile it that way (otherwise
    it doesn't release the allocated memory ever!).

    Look here: <http://hboehm.info/gc/> for instructions
    on how to download a version compatible with your compiler.
    '''
env = conf.Finish()
env.Append(LIBS = 'assignments')

for assignment in glob('./assignment*/'):
    env.Program(glob(path.join(assignment, '*.c')))

env.Doxygen("Doxyfile")
