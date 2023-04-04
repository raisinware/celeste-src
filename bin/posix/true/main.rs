// SPDX-License-Identifier: Apache-2.0 OR MIT
//! POSIX `true` command. Uses libc instead of rust std to reduce executable bloat.

#![no_std]
#![cfg_attr(not(test),no_main)] // cargo test doesnt like no_main

extern crate libc;

use core::panic::PanicInfo;
use libc::c_int;
use libc::EXIT_SUCCESS;

/// return EXIT_SUCCESS (0 on POSIX platforms)
#[cfg_attr(not(test), no_mangle)]
pub extern "C" fn main() -> c_int {
	return EXIT_SUCCESS
}

#[cold]
#[cfg_attr(not(test), panic_handler)]
fn _panic(_info: &PanicInfo) -> ! {
	loop {}
}

#[cfg(test)]
mod tests {
	use crate::main;
	use libc::EXIT_SUCCESS;

	#[test]
	fn test_true() {
		assert_eq!(main(), EXIT_SUCCESS);
	}
}
