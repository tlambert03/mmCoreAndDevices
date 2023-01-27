project('mmCoreAndDevices', 'cpp', version : '0.0.1',
	default_options: [
		'prefix=@0@'.format(meson.project_source_root() / 'stage'),
		'cpp_std=c++14',
	]
)

subproject('MMDevice')
subproject('MMCore')