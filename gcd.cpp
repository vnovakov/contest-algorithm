int gcd(int a, int b) {
	if (a == 0) {
		return b;
	}
	return gcd(b%a, a);
}

int totient_phi(int n) {
	int sum = 1;
	for (int i = 2; i < n; i++) {
		if (gcd(i, n) != 1) {
			continue;
		}
		sum += i;
	}
	return sum;
}