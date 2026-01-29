int prefix[3000][3000];
void init_prefix(int val, int R, int C, int Q[3001][3001]) {
    prefix[0][0] = 0;
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            prefix[i + 1][j + 1] = Q[i][j] <= val;
        }
    }

    for (int i = 1; i <= R; i++) {
        for (int j = 1; j <= C; j++) {
            prefix[i][j] += prefix[i - 1][j] + prefix[i][j - 1] - prefix[i - 1][j - 1];
        }
    }

}

bool f(int median, int H, int W, int R, int C, int Q[30001][3001]) {
    init_prefix(median, R, C, Q);
    int vals_before = (H * W) / 2 + 1;

    for (int i = 0; i <= R - H; i++) {
        for (int j = 0; j <= C - W; j++) {
            int count = prefix[i + H][j + W] - prefix[i][j + W] - prefix[i + H][j] + prefix[i][j];
            if (count >= vals_before) return 1;
        }
    }

    return 0;
}

int rectangle(int R, int C, int H, int W, int Q[3001][3001]) {
    int best_quality = 0;

    int lo = 1;
    int hi = R * C;
    while (lo <= hi) {
        int mid = (lo + hi) / 2;
        if (f(mid, H, W, R, C, Q)) {
            best_quality = mid;
            hi = mid - 1;
        } else {
            lo = mid + 1;
        }
    }

	return best_quality;
}
