bool = true
nmbr = 0
text = "string"
data = {
    true,
    1,
    "text",
    { ["key"] = "value"}
}

function func()
    return nmbr
end

more = {["foo"] = func}
