package EPICS::PodHtml;

use strict;
use warnings;

use base 'Pod::Simple::HTML';

# Translate L<link text|filename/Section name>
# into <a href="filename.html#Section-name">link text</a>

sub do_pod_link {
    # EPICS::PodHtml object and Pod::Simple::PullParserStartToken object
    my ($self, $link) = @_;

    my $ret;

    # Links to other EPICS POD files
    if ($link->tagname eq 'L' and $link->attr('type') eq 'pod') {
        my $to = $link->attr('to');
        my $section = $link->attr('section');

        $ret = $to ? "$to.html" : '';
        $ret .= "#$section" if $section;
    }
    else {
        # all other links are generated by the parent class
        $ret = $self->SUPER::do_pod_link($link);
    }

    return $ret;
}

# Generate the same section IDs as Pod::Simple::XHTML

sub section_name_tidy {
    my($self, $section) = @_;
    $section =~ s/^\s+//;
    $section =~ s/\s+$//;
    $section =~ tr/ /-/;
    $section =~ s/[[:cntrl:][:^ascii:]]//g; # drop crazy characters
    $section = $self->unicode_escape_url($section);
    $section = '_' unless length $section;
    return $section;
}

1;
