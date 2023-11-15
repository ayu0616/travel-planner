module.exports = {
    root: true,
    env: { browser: true, es2020: true },
    extends: [
        "eslint:recommended",
        "plugin:import/recommended",
        "plugin:import/warnings",
        "plugin:@typescript-eslint/recommended",
        "plugin:react-hooks/recommended",
        "plugin:storybook/recommended",
        "plugin:tailwindcss/recommended",
        "prettier",
    ],
    ignorePatterns: ["dist", ".eslintrc.cjs"],
    parser: "@typescript-eslint/parser",
    plugins: ["react-refresh", "typescript-sort-keys", "sort-keys-fix", "react", "tailwindcss"],
    parserOptions: {
        ecmaVersion: "latest",
        sourceType: "module",
        project: ["./tsconfig.json", "./tsconfig.node.json"],
        tsconfigRootDir: __dirname,
    },
    settings: {
        "import/resolver": {
            typescript: {},
        },
    },
    rules: {
        "react-refresh/only-export-components": ["warn", { allowConstantExport: true }],
        "@typescript-eslint/no-unused-vars": "warn",
        "import/order": [
            "warn",
            {
                groups: [
                    "builtin", // 組み込みモジュール
                    "external", // npmでインストールした外部ライブラリ
                    "internal", // 自作モジュール
                    ["parent", "sibling"],
                    "object",
                    "type",
                    "index",
                ],
                "newlines-between": "always", // グループ毎にで改行を入れる
                pathGroupsExcludedImportTypes: ["builtin"],
                alphabetize: {
                    order: "asc", // 昇順にソート
                    caseInsensitive: true, // 小文字大文字を区別する
                },
                pathGroups: [
                    // 指定した順番にソートされる
                    {
                        pattern: "@/components/common",
                        group: "internal",
                        position: "before",
                    },
                    {
                        pattern: "@/components/hooks",
                        group: "internal",
                        position: "before",
                    },
                ],
            },
        ],
        "react/jsx-sort-props": [
            "warn",
            {
                callbacksLast: true,
                shorthandFirst: true,
                shorthandLast: false,
                ignoreCase: true,
                noSortAlphabetically: false,
                reservedFirst: true,
            },
        ],
        "react-hooks/rules-of-hooks": "off",
        "prefer-template": "warn",
        "sort-keys-fix/sort-keys-fix": "warn",
        "typescript-sort-keys/interface": "warn",
        quotes: ["warn", "single"],
    },
};
