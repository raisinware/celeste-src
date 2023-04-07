// SPDX-License-Identifier: Apache-2.0 OR MIT
//! POSIX `true` command. return `()` (exit code 0 on POSIX platforms)

fn main() {
	()
}

#[cfg(test)]
mod tests {
	#[test]
	fn test_true() {
		assert_eq!(crate::main(), ());
	}
}
