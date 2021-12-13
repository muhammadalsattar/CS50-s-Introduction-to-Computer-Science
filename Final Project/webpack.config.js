const path = require('path')
const MiniCssExtractPlugin = require('mini-css-extract-plugin')


module.exports = (env) => {
    return {
        entry: './src/index.js',
        output: {
            path: path.resolve(__dirname, 'public/static'),
            filename: 'bundle.js'
        },
        module: {
            rules: [{
                test: /\.m?js$/,
                exclude: /node_modules/,
                use: {
                    loader: 'babel-loader',
                    options: {
                        presets: ['@babel/preset-env', '@babel/preset-react'],
                        plugins: ["@babel/plugin-proposal-class-properties"]
                    }
                }
            }, {
                test: /\.s?css$/,
                use: [MiniCssExtractPlugin.loader,
                    {
                        loader: 'css-loader',
                        options: {sourceMap: true}
                    },
                    {
                        loader: 'sass-loader',
                        options: {sourceMap: true}
                    }] 
            }]
        },
        plugins: [new MiniCssExtractPlugin({
            filename: 'styles.css'
        })],
        devServer: {
            static: {
                directory: path.resolve(__dirname, 'public/'),
                publicPath: '/'
            }
        },
        devtool: env.production? 'source-map': 'inline-source-map'
    }
}