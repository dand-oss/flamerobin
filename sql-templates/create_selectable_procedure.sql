{%confgui%}set term !! ;

create procedure SP_{%object_name%}
returns ( {%foreach:column:, :{%ifcontains:{%getconf:{%object_path%}/columnNames%}:{%object_name%}:
    {%object_name%} {%column_datatype%}%}%}
)
as
begin
    for select {%foreach:column:, :{%ifcontains:{%getconf:{%object_path%}/columnNames%}:{%object_name%}:
        a.{%object_name%}%}%}
    from {%object_name%} a
    into {%foreach:column:, :{%ifcontains:{%getconf:{%object_path%}/columnNames%}:{%object_name%}:
        {%object_name%}%}%} 
    do
    begin
        suspend;
    end
end!!

set term ; !!
