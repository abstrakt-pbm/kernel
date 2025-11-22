# Experimental kernel

## Building 
cmake --build --preset=lin_gcc
mv ./bin/kernel.elf ./bin/iso/boot/kernel.elf
grub-mkrescue -o ./bin/kernel.iso ./bin/iso

## Start
qemu-system-x86_64 \
  -bios /usr/share/OVMF/x64/OVMF_CODE.fd \
  -drive format=raw,file=./bin/kernel.iso \
  -m 4G \
  -vga virtio \
  -S \
  -gdb tcp::1234

## Screenshots
![Terminal HelloWorld](screenshots/terminal_helloworld.png)
