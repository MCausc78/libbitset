#!/usr/bin/env ruby

def usage
	puts <<TXT
#{__FILE__}: usage: #{__FILE__} ACTION
Available actions:
	build		Build library
	clean		Clean binaries
	install		Install binaries
	uninstall	Uninstall binaries
TXT
end

prefix = "/usr"
if ENV.has_key? "PREFIX"
	prefix = ENV["PREFIX"]
end

project = {
	:files => {
		:src => [
			"src/libbitset/bitset.c",
			"src/libbitset/reader.c",
			"src/libbitset/writer.c"
		],
		:include => [
			"src/libbitset/bitset.h",
			"src/libbitset/reader.h",
			"src/libbitset/writer.h"
		]
	},
	:output => "libbitset.so",
	:cc => {
		:args => [
			"-fPIC",
			"-shared",
			"-Isrc",
			"-ldystring"
		]
	}
}

case ARGV[0]
when nil
	usage
	exit! 1
when "build"
	print `mkdir -p build/include build/lib`
	print `gcc #{project[:cc][:args].join ' '} -o build/lib/#{project[:output]} #{project[:files][:src].join ' '}`
	print `cp -r src/. build/include/`
	print `bash -c "shopt -s globstar; rm -f build/include/**/**/**/**.c"`
when "clean"
	print `rm -rf build`
when "install"
	print `cp -r build/. #{prefix}/`
when "uninstall"
	print `rm -rf #{
project[:files][:include].each { |s|
	prefix + "include" + s
}.join ' '} #{prefix}/lib/#{project[:output]}`
else
	$stderr.puts "#{__FILE__}: unknown action: \"#{ARGV[0]}\""
	exit! 2
end
exit! 0
