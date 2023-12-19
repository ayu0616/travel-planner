module.exports = {
    extends: ["plugin:import/recommended", "plugin:import/warnings", "prettier"],
    parser: "@typescript-eslint/parser",
    plugins: ["typescript-sort-keys", "sort-keys-fix", "react"],
    rules: {
        "import/order": [
            "warn",
            {
                alphabetize: {
                    // 昇順にソート
                    caseInsensitive: true,
                    order: "asc", // 小文字大文字を区別する
                },
                groups: [
                    "builtin", // 組み込みモジュール
                    "external", // npmでインストールした外部ライブラリ
                    "internal", // 自作モジュール
                    ["parent", "sibling"],
                    "object",
                    "type",
                    "index",
                ],
                "newlines-between": "always",

                pathGroups: [
                    // 指定した順番にソートされる
                    {
                        group: "internal",
                        pattern: "@/components/common",
                        position: "before",
                    },
                    {
                        group: "internal",
                        pattern: "@/components/hooks",
                        position: "before",
                    },
                ],
                // グループ毎にで改行を入れる
                pathGroupsExcludedImportTypes: ["builtin"],
            },
        ],
        "object-shorthand": ["warn", "always"],
        "prefer-template": "warn",
        "react-hooks/rules-of-hooks": "off",
        "react/jsx-sort-props": [
            "warn",
            {
                callbacksLast: true,
                ignoreCase: true,
                noSortAlphabetically: false,
                reservedFirst: true,
                shorthandFirst: true,
                shorthandLast: false,
            },
        ],
        "sort-keys-fix/sort-keys-fix": "warn",
        "typescript-sort-keys/interface": "warn",
    },
    settings: {
        "import/resolver": {
            node: {
                extensions: [".js", ".jsx", ".ts", ".tsx"],
                paths: ["src"],
            },
        },
    },
};
