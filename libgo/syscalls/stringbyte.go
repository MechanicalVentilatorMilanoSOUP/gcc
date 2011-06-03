// stringbyte.go -- string to bytes functions.

// Copyright 2010 The Go Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

package syscall

import "unsafe"

// StringByteSlice returns a NUL-terminated slice of bytes
// containing the text of s.
func StringByteSlice(s string) []byte {
	a := make([]byte, len(s)+1);
	for i := 0; i < len(s); i++ {
		a[i] = s[i];
	}
	return a;
}

// StringBytePtr returns a pointer to a NUL-terminated array of bytes
// containing the text of s.
func StringBytePtr(s string) *byte {
	p := StringByteSlice(s);
	return &p[0];
}

// BytePtrToString takes a NUL-terminated array of bytes and convert
// it to a Go string.
func BytePtrToString(p *byte) string {
	a := (*[10000]byte)(unsafe.Pointer(p))
	i := 0
	for a[i] != 0 {
		i++
	}
	return string(a[:i])
}
