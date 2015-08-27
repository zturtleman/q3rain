# Prerequesites #
1. You **do** need Quake III Arena with 1.32c patch. Q3Rain is sadly not standalone yet.

If you want to compile q3rain yourself, "hg clone" the source code. You will need to have libsdl-dev installed.
A simple
`make`
will compile the QVMs.

# Installing #
  1. Inside your Quake III Arena installation directory, create a folder 'rain'. (~/.q3a/ on Linux works fine)
  1. Download the rain-vm.pk3 and rain-assets.pk3 files from our [Download Page](http://code.google.com/p/q3rain/downloads/list) and store them in the previously created folder.
  1. Either start Quake III Arena and choose 'rain' from the Mods-Menu, or start it like this:
> `quake3.exe/ioquake3.i386/ioquake3.x86_64 +set fs_game rain`

Please note the menu doesn't work and we do not have custom maps yet. To start playing, open the console (~) and type
> ` /map q3dm1`
Then add bots via the menu/console.