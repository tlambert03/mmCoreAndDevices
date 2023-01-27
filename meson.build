project('mmCoreAndDevices', 'cpp', version : '0.0.1',
	default_options: [
		'prefix=@0@'.format(meson.project_source_root() / 'stage'),
		'cpp_std=c++14',
	]
)

subproject('MMDevice')
subproject('MMCore')
# having this line not here allows the project
#to still run if the project is missing. If the project isn't missing then it
#will still be detected when needed.
#subproject('3rdPartyPrivate')

# if get_option('MMCOREJ')
# 	subproject('MMCoreJ_wrap')
# endif

# if get_option('DEVICE_ADAPTERS')
# 	subproject('DeviceAdapters')
# endif

# if get_option('MMCOREPY')
# 	subproject('MMCorePy_wrap')
# endif