# ベースイメージを指定
FROM node:14

# 作業ディレクトリを設定
WORKDIR /app

# package.jsonとpackage-lock.jsonをコピー
COPY package*.json ./

# 依存パッケージをインストール
RUN npm install

# ソースコードをコピー
COPY . .

# ポートを設定
EXPOSE 5173

# 開発サーバーを起動
CMD ["npm", "run", "dev"]
