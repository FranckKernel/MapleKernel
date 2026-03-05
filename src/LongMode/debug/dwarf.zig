const std = @import("std");

// Note, we are using 64 bit version. 32 bit version will crash the program

pub const DebugLineHeader = packed struct {
    length: u32,
    version: u16,
    header_length: u32,
    min_instruction_length: u8,
    default_is_stmt: u8,
    line_base: i8,
    line_range: u8,
    opcode_base: u8,
    // std_opcode_lengths: [12]u8,
    // Why can't i just fucking have the above?
};

pub const DebugInfoHeader = packed struct {
    all_fs: u32,
    length: u64,
    version: u16,
    unit_type: u8,
    address_size: u8,
    debug_abbrev_offset: u64,
    type_signature: u64,
    type_offset: u64,
    // first die begins here
};
