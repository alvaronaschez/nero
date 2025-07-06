add-highlighter global/ number-lines -relative
add-highlighter global/ number-lines


# kak-lsp
#if [ -x "$(command -v kak-lsp)" ]; then
  # enable kakoune lsp
  eval %sh{kak-lsp}
  hook global WinSetOption filetype=(rust|python|go|javascript|typescript|c|cpp) %{
    lsp-enable-window
  }

  # key mappings
  map global user l ':enter-user-mode lsp<ret>' -docstring 'LSP mode'

  map global insert <tab> '<a-;>:try lsp-snippets-select-next-placeholders catch %{ execute-keys -with-hooks <lt>tab> }<ret>' -docstring 'Select next snippet placeholder'

  map global object a '<a-semicolon>lsp-object<ret>' -docstring 'LSP any symbol'
  map global object <a-a> '<a-semicolon>lsp-object<ret>' -docstring 'LSP any symbol'
  map global object f '<a-semicolon>lsp-object Function Method<ret>' -docstring 'LSP function or method'
  map global object t '<a-semicolon>lsp-object Class Interface Struct<ret>' -docstring 'LSP class interface or struct'
  map global object d '<a-semicolon>lsp-diagnostic-object --include-warnings<ret>' -docstring 'LSP errors and warnings'
  map global object D '<a-semicolon>lsp-diagnostic-object<ret>' -docstring 'LSP errors'

#fi

