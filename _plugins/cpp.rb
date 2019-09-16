module Jekyll
  class CppTag < Liquid::Tag

    def initialize(tag_name, markup, token)
      super
      @fn = token
    end

    def render(context)
      "#{HighlightCode::highlight(#{IncludeRelative, @fn}, C++)}"
    end
  end
end

Liquid::Template.register_tag('cpp', Jekyll::CppTag)
