# -*- mode: python -*-

from glob import glob
from sys import stdout
from os import path
from subprocess import call

generate_documentation = False

dll = SharedLibrary('./lib/assignments', glob('./lib/*.c') + glob('./lib/*/*.c'), CPPPATH = ['./lib'])
env = Environment(tools = ["default", "doxygen"],
                  CPPPATH = './lib',
                  LIBPATH = './lib')

if env['PLATFORM'] != 'posix':
    env.MSVSProject(target = 'assignment14' + env['MSVSPROJECTSUFFIX'],
                srcs = glob('./lib/*.c'),
                buildtarget = dll,
                variant = 'Release')

def CheckDoxygen(context):
    context.Message('Checking for Doxygen... ')
    result = 1
    try:
        call(['doxygen', '--version'])
    except:
        result = 0
    context.Result(result)
    return result

conf = Configure(env, custom_tests = {'CheckDoxygen' : CheckDoxygen})
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
if conf.CheckDoxygen():
    print 'Will generate documentation'
    generate_documentation = False
else:
    print '''
    This project can generate documentation, but Doxygen,
    the program needed to do so cannot be found.  If you
    want documentation generated, install this program
    following the instructions here: 
    <https://www.stack.nl/~dimitri/doxygen/manual/install.html>
    and re-run the build.
    '''

env = conf.Finish()
env.Append(LIBS = 'assignments')

for assignment in glob('./assignment*/'):
    env.Program(assignment + '/' + assignment.replace('-', ''),
                glob(path.join(assignment, '*.c')))

if generate_documentation:
    env.Doxygen('Doxyfile')
