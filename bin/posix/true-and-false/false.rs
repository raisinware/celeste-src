// SPDX-License-Identifier: Apache-2.0 OR MIT
//! POSIX `false` command. Returns `ExitCode::FAILURE`
//! (exit code 1 on POSIX platforms)

use std::process::ExitCode;

fn main() -> ExitCode {
	ExitCode::FAILURE
}

// no tests here because ExitCode does not implement PartialEq
