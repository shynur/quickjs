((auto-mode-alist . (("[~#]\\'" . (ignore t))
                     ("/.git/COMMIT_EDITMSG\\'" . diff-mode)
                     ("/CMakeLists\\.txt\\'" . cmake-ts-mode)
                     ("\\.cmake\\'" . cmake-ts-mode)
                     ("\\.ya?ml\\'" . yaml-ts-mode)
                     ("\\.json\\'" . js-json-mode)
                     ("\\.mjs\\'" . javascript-mode)))
 (nil . ((eval . (when (derived-mode-p 'text-mode 'prog-mode 'conf-mode)
                   (add-hook 'before-save-hook
                             #'delete-trailing-whitespace
                             nil "local")))
         (delete-trailing-lines . t)
         (require-final-newline . t)
         (sentence-end-double-space . t)

         (eval . (when buffer-file-name
                   (when (string-match-p
                           "\\`\\(LICENSE\\|License\\|license\\|COPYING\\)\\'"
                           (file-name-base buffer-file-name))
                     (setq-local buffer-read-only t))))

         (eval . (line-number-mode -1))
         (mode . display-line-numbers)
         (mode . column-number)

         (read-file-name-completion-ignore-case . t)

         (mode . auto-save)

         (treesit-font-lock-level . 4)))
 (makefile-mode . ((whitespace-style . (face tabs))
                   (mode . whitespace)))
 (markdown-mode . ((markdown-fontify-code-blocks-natively . t)))
 (js-json-mode . ((indent-tabs-mode . t)
                  (tab-width . 4)))
 (js-mode . ((indent-tabs-mode . nil)
             (tab-width . 4)))
 (yaml-mode . ((indent-tabs-mode . nil)
               (tab-width . 2))))
