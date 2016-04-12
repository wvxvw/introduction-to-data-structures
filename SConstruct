from glob import glob
from sys import stdout
from os import path

SharedLibrary('./lib/assignments', glob('./lib/*.c'))
env = Environment(CPPPATH = './lib',
                  LIBS = ['assignments', 'm', 'gc'],
                  LIBPATH = './lib')

for assignment in glob('./assignment*/'):
    env.Program(glob(path.join(assignment, '*.c')))
