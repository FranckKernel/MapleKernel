// panic.zig
const std = @import("std");
const stdio = @import("stdio");
const builtin = @import("builtin");

const dwarf = @import("dwarf.zig");

pub fn panic(msg: []const u8, src: std.builtin.SourceLocation) noreturn {
    stdio.string_writter(msg);

    stdio.string_writter("\nThe module name: ");
    stdio.string_writter(src.module);
    stdio.string_writter("\nThe file name: ");
    stdio.string_writter(src.file);
    stdio.string_writter("\nThe function name: ");
    stdio.string_writter(src.fn_name);
    stdio.string_writter("\nThe Line: ");
    stdio.print_uint(src.line);
    stdio.string_writter("\nThe Column: ");
    stdio.print_uint(src.column);

    while (true) {
        asm volatile ("cli");
        asm volatile ("hlt");
    }
}

pub inline fn assert(cond: bool, msg: []const u8, src: std.builtin.SourceLocation) void {
    comptime if (builtin.mode == .ReleaseFast or builtin.mode == .ReleaseSmall) {
        return;
    };
    if (!cond) {
        panic(msg, src);
        // passing src here cause @src.fn_name = assert
    }
}

// Symbols from linker script

extern var __debug_abbrev_start: u8;
extern var __debug_abbrev_end: u8;
extern var __debug_str_start: u8;
extern var __debug_str_end: u8;
extern var __debug_line_start: u8;
extern var __debug_line_end: u8;
extern var __debug_ranges_start: u8;
extern var __debug_ranges_end: u8;

extern const __debug_info_start: u32;
extern var __debug_info_end: u32;

pub fn first_debug() void {
    stdio.printf("\n====First Debug information test====\n", .{});

    const a: *const u32 = &__debug_info_start;
    stdio.printf("address: {}\n", .{a});
    stdio.printf("all fs: {}", .{a.*});

    // stdio.printf("size: {}\n", .{@sizeOf(dwarf.DebugInfoHeader)});
    // stdio.printf("align: {}\n", .{@alignOf(dwarf.DebugInfoHeader)});

    // const dis: *dwarf.DebugInfoHeader = @ptrCast(@alignCast(&__debug_info_start));
    // const dis: *dwarf.DebugInfoHeader = @ptrFromInt(__debug_info_start);
    // const dis: *dwarf.DebugInfoHeader = @ptrFromInt(0xffffffff80013210);
    // stdio.printf("debug information: \n{}\n", .{dis.*});

    // stdio.printf("Read it successfuly\n", .{});

    // stdio.printf("debug info start address {}\n", .{&__debug_info_start});
    // stdio.printf("debug info first u32 value {}\n", .{__debug_info_start});

}
