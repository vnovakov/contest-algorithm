int gcd(int a, int b) {
	if (a == 0) {
		return b;
	}
	return gcd(b%a, a);
}

int totient_phi(int n) {
	int count = 1;
	for (int i = 2; i < n; i++) {
		count += gcd(i, n) == 1;
	}
	return count;
}