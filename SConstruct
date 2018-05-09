#!python

# This SConstruct orchestrates building RAF NetCDF Utility programs.

import os
import sys
sys.path.append('vardb/site_scons')
import eol_scons

AddOption('--prefix',
  dest='prefix',
  type='string',
  nargs=1,
  action='store',
  metavar='DIR',
  default='#',
  help='installation prefix')

def NC_utils(env):
    if GetOption('prefix') != "#":
        env.Replace(DEFAULT_INSTALL_PREFIX = GetOption('prefix'))
        env.Replace(DEFAULT_OPT_PREFIX = GetOption('prefix'))
    else:
        env['DEFAULT_INSTALL_PREFIX']="#"
        env['DEFAULT_OPT_PREFIX']="#"

    env.Require(['prefixoptions'])

    env.Append(CPPPATH=[env['OPT_PREFIX']+'/include']) 

env = Environment(GLOBAL_TOOLS = [NC_utils])

def VARDB_opt(env):
    env.Append(CPPPATH=[env['OPT_PREFIX']+'/vardb'])
    env.Append(LIBS=['VarDB'])

if env['DEFAULT_OPT_PREFIX'] == "#":
    SConscript('vardb/SConscript')
else:
   vardb = VARDB_opt
   Export('vardb')

SConscript('asc2cdf/SConscript')
SConscript('asc2cdf_HRT/SConscript')
SConscript('flt_time/SConscript')
SConscript('mkcdf/SConscript')
SConscript('n2asc/SConscript')
#nc2asc/
SConscript('nc2iwg1/SConscript')
SConscript('ncav/SConscript')
SConscript('nc_compare/SConscript')
SConscript('nc_dips/SConscript')
SConscript('ncextr/SConscript')
SConscript('ncfillvar/SConscript')
SConscript('nc_gap/SConscript')
SConscript('ncmerge/SConscript')
SConscript('ncReorder/SConscript')
SConscript('nc_sane/SConscript')
SConscript('ncstat/SConscript')
SConscript('ncvarlist/SConscript')
