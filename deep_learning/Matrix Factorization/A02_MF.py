class MF():
    def __init__(self, k=64):
        self.k = k
        
        self.R = None
        self.P = np.random.normal(loc=0.0, scale=1/k, size=(256, self.k))
        self.Q = np.random.normal(loc=0.0, scale=1/k, size=(256, self.k))


    def train(self, R, reg_lambda, lr_alpha, max_iterations, epsilon):
        self.R = np.array(R)

        for iteration in tqdm(range(max_iterations)):
            for i in range(256):
                for j in range(256):
                    if self.R[i][j] > 0:
                        error = self.R[i][j] - np.dot(self.P[i, :], self.Q[j, :].T)
                        self.P[i, :] += lr_alpha * (2 * error * self.Q[j, :] - 2 * reg_lambda * self.P[i, :])
                        self.Q[j, :] += lr_alpha * (2 * error * self.P[i, :] - 2 * reg_lambda * self.Q[j, :])

            reconst_R = np.dot(self.P, self.Q.T)
            error_matrix = self.R - reconst_R
            error = np.sum(np.square(error_matrix))

            if error < epsilon:
                break

        return 1

    def P_MultipliedBy_Q_Transpose(self):
        reconst_R = np.dot(self.P, self.Q.T)
        return reconst_R
